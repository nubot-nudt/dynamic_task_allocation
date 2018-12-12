#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
import argparse
import numpy as np

from gym import spaces
from allocation_common.srv import *
from allocation_common.msg import terminal2DQN_info
from dqn_Double import DoubleDQN
from dqn_PER import DQNPrioritizedReplay
from dqn_Dueling import DuelingDQN

def parse_args():
    parser = argparse.ArgumentParser('Deep Reinforcement Learning for task allocation')
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
    # observation = [req.observation.Agent_ID, req.observation.robot_pos.x, req.observation.robot_pos.y]
    # observation = [req.observation.robot_pos.x, req.observation.robot_pos.y]

    # the information about teammates
    # for i in range(len(req.observation.teammatesinfo)):
    #     observation.append(req.observation.teammatesinfo[i].robot_pos.x)
    #     observation.append(req.observation.teammatesinfo[i].robot_pos.y)
        # observation.append(req.observation.teammatesinfo[i].which_task)

    # the information about tasks
    # for j in range(len(req.observation.tasksinfo)):
        # observation.append(req.observation.tasksinfo[j].task_ID)
        # observation.append(req.observation.tasksinfo[j].task_pos.x)
        # observation.append(req.observation.tasksinfo[j].task_pos.y)
        # observation.append(req.observation.tasksinfo[j].task_status)
        # observation.append(req.observation.tasksinfo[j].is_target)

    # if len(observation) != observation_space.shape[0]:
    #     print('the space of the observation is unmatched')
    #     return GetActionResponse(-1)

    observation = np.zeros((map_size*map_size), dtype=np.int)
    task_status = np.ones(action_space.n, dtype=np.int)
    # the information about teammates
    for i in range(len(req.observation.teammatesinfo)):
        tmp_x = int(req.observation.teammatesinfo[i].robot_pos.x+map_size/2)
        tmp_y = int(req.observation.teammatesinfo[i].robot_pos.y+map_size/2)
        if tmp_x * map_size + tmp_y >= 0 and tmp_x * map_size + tmp_y < map_size * map_size:
            observation[tmp_x * map_size + tmp_y] = -1

    tmp_x = int(req.observation.robot_pos.x+map_size/2)
    tmp_y = int(req.observation.robot_pos.y+map_size/2)
    if tmp_x * map_size + tmp_y >= 0 and tmp_x * map_size + tmp_y < map_size * map_size:
        observation[tmp_x * map_size + tmp_y] = -2

    # the information about tasks
    for j in range(len(req.observation.tasksinfo)):
        tmp_x = int(req.observation.tasksinfo[j].task_pos.x + map_size / 2)
        tmp_y = int(req.observation.tasksinfo[j].task_pos.y + map_size / 2)
        if tmp_x * map_size + tmp_y >= 0 and tmp_x * map_size + tmp_y < map_size * map_size:
            observation[tmp_x * map_size + tmp_y] = req.observation.tasksinfo[j].task_status
        task_status[req.observation.tasksinfo[j].task_ID + 1] = req.observation.tasksinfo[j].task_status

    action = DQN.choose_action(observation, task_status)
    # record the observation and action
    observation_space_n[req.observation.Agent_ID] = observation
    action_space_n[req.observation.Agent_ID] = action

    # if action != 0:
    #     print('Agent {} get the allocated task {}'.format(req.observation.Agent_ID, action-1))
    return GetActionResponse(action)

def return_reward_callback(req):
    global train_step
    # the information about own
    # observation_ = [req.observation_.Agent_ID, req.observation_.robot_pos.x, req.observation_.robot_pos.y]
    # observation_ = [req.observation_.robot_pos.x, req.observation_.robot_pos.y]

    # the information about teammates
    # for i in range(len(req.observation_.teammatesinfo)):
    #     observation_.append(req.observation_.teammatesinfo[i].robot_pos.x)
    #     observation_.append(req.observation_.teammatesinfo[i].robot_pos.y)
        # observation_.append(req.observation_.teammatesinfo[i].which_task)

    # the information about tasks
    # for j in range(len(req.observation_.tasksinfo)):
        # observation_.append(req.observation_.tasksinfo[j].task_ID)
        # observation_.append(req.observation_.tasksinfo[j].task_pos.x)
        # observation_.append(req.observation_.tasksinfo[j].task_pos.y)
        # observation_.append(req.observation_.tasksinfo[j].task_status)
        # observation_.append(req.observation_.tasksinfo[j].is_target)

    # if len(observation_) != observation_space.shape[0]:
    #     print('the space of the observation is unmatched')
    #     return ReturnRewardResponse(False)

    # observation_ = np.zeros((map_size*map_size), dtype=np.int)
    observation_ = observation_space_n[req.observation_.Agent_ID]
    # the information about tasks
    for j in range(len(req.observation_.tasksinfo)):
        tmp_x = int(req.observation_.tasksinfo[j].task_pos.x+map_size/2)
        tmp_y = int(req.observation_.tasksinfo[j].task_pos.y+map_size/2)
        if tmp_x * map_size + tmp_y >= 0 and tmp_x * map_size + tmp_y < map_size * map_size:
            observation_[tmp_x * map_size + tmp_y] = req.observation_.tasksinfo[j].task_status
    # # the information about teammates
    # for i in range(len(req.observation_.teammatesinfo)):
    #     tmp_x = int(req.observation_.teammatesinfo[i].robot_pos.x+map_size/2)
    #     tmp_y = int(req.observation_.teammatesinfo[i].robot_pos.y+map_size/2)
    #     if tmp_x * map_size + tmp_y >= 0 & tmp_x * map_size + tmp_y < map_size * map_size:
    #         observation_[tmp_x * map_size + tmp_y] = -1
    #
    # tmp_x = int(req.observation_.robot_pos.x+map_size/2)
    # tmp_y = int(req.observation_.robot_pos.y+map_size/2)
    # if tmp_x * map_size + tmp_y >= 0 & tmp_x * map_size + tmp_y < map_size*map_size:
    #     observation_[tmp_x * map_size + tmp_y] = -2

    reward_n.append(req.reward)
    # print(observation_)
    DQN.store_transition(observation_space_n[req.observation_.Agent_ID], action_space_n[req.observation_.Agent_ID],
                         req.reward, observation_)

    if (train_step > 200) and (train_step % 5 == 0):
        DQN.learn()
    train_step += 1
    # print('complete {} train'.format(train_step))

    return ReturnRewardResponse(True)

def dqn_callback(data):
    # global parameters
    global team_number
    global task_number
    global action_space
    global observation_space
    global action_space_n
    global observation_space_n
    global DQN
    global train_step
    global map_size
    # global last_step
    global reward_n
    global reward_average
    # global total_reward

    # finish a episode
    if data.finish_episode:
        print(sum(reward_n)/len(reward_n), len(reward_n))
        reward_average.append(sum(reward_n)/len(reward_n))
        reward_n.clear()
        return
    # finish the train and plot the cost
    if data.finish_train:
        reward_average.append(sum(reward_n)/len(reward_n))
        reward_n.clear()
        print('finish the train')
        # DQN.plot_cost()
        # plot_reward()
        return

    team_number = data.team_number
    task_number = data.task_number
    action_space_n = []
    observation_space_n = []
    reward_n = []
    reward_average = []
    train_step = 0
    last_step = 0
    total_reward = 0
    map_size = 16

    # action_space
    action_space = spaces.Discrete(task_number+1)
    # observation_space
    # observation_space = spaces.Box(low=-np.inf, high=+np.inf, shape=(team_number*2+task_number*2,), dtype=np.float32)
    observation_space = spaces.Box(low=-np.inf, high=+np.inf, shape=(map_size*map_size,), dtype=np.int)

    for i in range(team_number):
        action_space_n.append(action_space)
        observation_space_n.append(observation_space)

    # get the DQN trainer
    print('Init the DQN Trainer...')

    # DQN = DeepQNetwork(n_actions=action_space.n, n_features=observation_space.shape[0],
    #                    learning_rate=0.01, e_greedy=0.9, replace_target_iter=300, memory_size=3000,
    #                    e_greedy_increment=None, )
    #
    # DQN = DoubleDQN(n_actions=action_space.n, n_features=observation_space.shape[0],
    #                 learning_rate=0.01, e_greedy=0.9, replace_target_iter=300, memory_size=3000,
    #                 e_greedy_increment=None, double_q=True, )

    DQN = DQNPrioritizedReplay(n_actions=action_space.n, n_features=observation_space.shape[0],
                               learning_rate=0.01, e_greedy=0.9, replace_target_iter=300, memory_size=3000,
                               e_greedy_increment=None, prioritized=True, )

    # print(action_space, observation_space, action_space_n, observation_space_n)

def plot_reward():
    import matplotlib.pyplot as plt
    plt.plot(np.arange(len(reward_average)), reward_average)
    plt.ylabel('Average reward')
    plt.xlabel('Episode')
    plt.show()


if __name__ == '__main__':
    # init some parameters
    arg_list = parse_args()
    init_ros()
