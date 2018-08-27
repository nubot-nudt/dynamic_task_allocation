#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
import argparse
import gym
import time
import numpy as np

from gym import spaces
from std_msgs.msg import String
from allocation_common.srv import *
from allocation_common.msg import terminal2DQN_info
from reinforcement_learning import DeepQNetwork

def parse_args():
    parser = argparse.ArgumentParser("Reinforcement Learning for task allocation")
    return parser.parse_args()

def init_ros():
    # start the ROS callback
    print('Starting ROS Process...')
    rospy.init_node('dqn_ros', anonymous=True)
    rospy.Subscriber('/control_terminal/terminal2DQN_info', terminal2DQN_info, dqn_callback)
    rospy.Service('/dqn_ros/get_action', GetAction, get_action_callback)
    rospy.Service('/dqn_ros/return_reward', ReturnReward, return_reward_callback)
    rospy.spin()

def get_action_callback(req):
    # the information about own
    observation = [req.observation.Agent_ID, req.observation.robot_pos.x, req.observation.robot_pos.y]

    # the information about teammates
    for i in range(len(req.observation.teammatesinfo)):
        observation.append(req.observation.teammatesinfo[i].robot_pos.x)
        observation.append(req.observation.teammatesinfo[i].robot_pos.y)
        observation.append(req.observation.teammatesinfo[i].which_task)

    # the information about tasks
    for j in range(len(req.observation.tasksinfo)):
        observation.append(req.observation.tasksinfo[j].task_ID)
        observation.append(req.observation.tasksinfo[j].task_pos.x)
        observation.append(req.observation.tasksinfo[j].task_pos.y)
        observation.append(req.observation.tasksinfo[j].task_status)
        observation.append(req.observation.tasksinfo[j].is_target)

    if len(observation) != observation_space.shape[0]:
        print("the space of the observation is unmatched")
        return GetActionResponse(-1)

    observation_array = np.array(observation)
    action = DQN.choose_action(observation_array)
    # record the observation and action
    observation_space_n[req.observation.Agent_ID] = observation_array
    action_space_n[req.observation.Agent_ID] = action

    print("get the allocated task")
    return GetActionResponse(action)

def return_reward_callback(req):
    global train_step
    # the information about own
    observation_ = [req.observation_.Agent_ID, req.observation_.robot_pos.x, req.observation_.robot_pos.y]

    # the information about teammates
    for i in range(len(req.observation_.teammatesinfo)):
        observation_.append(req.observation_.teammatesinfo[i].robot_pos.x)
        observation_.append(req.observation_.teammatesinfo[i].robot_pos.y)
        observation_.append(req.observation_.teammatesinfo[i].which_task)

    # the information about tasks
    for j in range(len(req.observation_.tasksinfo)):
        observation_.append(req.observation_.tasksinfo[j].task_ID)
        observation_.append(req.observation_.tasksinfo[j].task_pos.x)
        observation_.append(req.observation_.tasksinfo[j].task_pos.y)
        observation_.append(req.observation_.tasksinfo[j].task_status)
        observation_.append(req.observation_.tasksinfo[j].is_target)

    if len(observation_) != observation_space.shape[0]:
        print("the space of the observation is unmatched")
        return ReturnRewardResponse(False)

    observation_array_ = np.array(observation_)
    DQN.store_transition(observation_space_n[req.observation_.Agent_ID], action_space_n[req.observation_.Agent_ID],
                         req.reward, observation_array_)

    if (train_step > 200) and (train_step % 5 == 0):
        DQN.learn()
    train_step = +1
    print("complete a train")
    return ReturnRewardResponse(True)

def dqn_callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'initialize the DQN train')

    global team_number
    global task_number
    global action_space
    global observation_space
    global action_space_n
    global observation_space_n
    global DQN
    global train_step

    team_number = data.team_number
    task_number = data.task_number
    train_step = 0
    action_space_n = []
    observation_space_n = []

    # action_space
    action_space = spaces.Discrete(task_number + 1)
    # observation_space
    observation_space = spaces.Box(low=-np.inf, high=+np.inf, shape=(team_number*3+task_number*5,), dtype=np.float32)

    for i in range(team_number):
        action_space_n.append(action_space)
        observation_space_n.append(observation_space)

    # get the DQN trainer
    print('Init the DQN Trainer...')

    DQN = DeepQNetwork(n_actions=action_space.n, n_features=observation_space.shape[0],
                       learning_rate=0.001, e_greedy=0.9, replace_target_iter=300, memory_size=3000,
                       e_greedy_increment=0.0001, )

    # print(action_space, observation_space, action_space_n, observation_space_n)


if __name__ == '__main__':
    # init some parameters
    arg_list = parse_args()
    init_ros()
