#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import rospy
import argparse
import numpy as np
import math

from gym import spaces
from allocation_common.msg import terminal2DQN_info
from dqn_Dueling import DuelingDQN
# from RL import DDPG

def parse_args():
    parser = argparse.ArgumentParser('Deep Reinforcement Learning for task allocation')
    return parser.parse_args()

def init_ros():
    # start the ROS callback
    print('Starting ROS Process...')
    global MAX_EPISODES
    global MAX_EP_STEPS
    MAX_EPISODES = 5000
    MAX_EP_STEPS = 200
    rospy.init_node('dqn_ros', anonymous=True)
    rospy.Subscriber('/control_terminal/terminal2DQN_info', terminal2DQN_info, dqn_callback)
    rospy.spin()

def dqn_callback(data):
    global rl
    global s_init
    global task_pos_x
    global task_pos_y
    global team_number
    global task_number
    global map_size

    s_init = []
    task_pos_x = []
    task_pos_y = []
    team_number = len(data.robot_pos_x)
    task_number = len(data.task_pos_x)
    map_size = 6

    for i in range(len(data.task_pos_x)):
        task_pos_x.append(data.task_pos_x[i])
        task_pos_y.append(data.task_pos_y[i])

    # get the DQN trainer
    print('Init the DQN Trainer...')

    action_space = spaces.Discrete(10)
    observation_space = spaces.Box(low=-np.inf, high=+np.inf, shape=((team_number+task_number) * 3,), dtype=np.int)
    # rl = DDPG(team_number, (team_number+task_number)*3, [0, task_number])
    rl = DuelingDQN(n_actions=action_space.n, n_features=observation_space.shape[0],
                    learning_rate=0.01, e_greedy=0.9, replace_target_iter=300, memory_size=3000,
                    e_greedy_increment=0.001, )

    # the information about robots
    for i in range(team_number):
        s_init.append(data.robot_pos_x[i])
        s_init.append(data.robot_pos_y[i])
        s_init.append(0)

    # the information about tasks
    for j in range(task_number):
        s_init.append(data.task_pos_x[j])
        s_init.append(data.task_pos_y[j])
        s_init.append(0)

    s_init = np.array(s_init)
    train()

def step(a, s):
    global last_sum_dis
    global last_max_dis
    global last_count
    s_ = s.copy()
    dis = []
    count = task_number
    done = False
    for i in range(len(a)):
        # for robots info
        task_choose = a[i]
        # task_choose = math.floor(a[i])
        distance = math.sqrt(math.pow(task_pos_x[task_choose]-s_[i*3], 2)
                             + math.pow(task_pos_y[task_choose]-s_[i*3+1], 2))
        s_[i*3] = task_pos_x[task_choose]
        s_[i*3+1] = task_pos_y[task_choose]
        s_[i*3+2] += distance
        dis.append(s_[i*3+2])
        # for tasks info
        s_[team_number*3+task_choose*3+2] = 1

    for j in range(task_number):
        if s_[team_number*3+j*3+2] == 1:
            count -= 1

    r = (last_sum_dis - sum(dis)) + (last_max_dis - max(dis)) + (last_count - count)
    # r = -count
    if count == 0:
        done = True
    last_count = count
    last_max_dis = max(dis)
    last_sum_dis = sum(dis)
    # print(s)
    return s_, r, done

def train():
    global last_sum_dis
    global last_max_dis
    global last_count
    train_step = 0
    a = []
    # start training
    for i in range(MAX_EPISODES):
        s = s_init.copy()
        last_sum_dis = 0
        last_max_dis = 0
        last_count = task_number
        ep_r = 0.
        for j in range(MAX_EP_STEPS):
            action = rl.choose_action(s)
            # print(action)
            # a.append(math.floor(action/100))
            # a.append(math.floor((action-a[0]*100)/10))
            # a.append(action-a[0]*100-a[1]*10)

            # a.append(math.floor(action/10))
            # a.append(action-a[0]*10)

            a.append(action)
            print(a)

            s_, r, done = step(a, s)
            a.clear()
            # s_, r, done = step(action, s)
            rl.store_transition(s, action, r, s_)
            ep_r += r

            if (train_step > 200) and (train_step % 5 == 0):
                rl.learn()
            train_step += 1
            # if rl.memory_full:
                # start to learn once has fulfilled the memory
                # rl.learn()
            s = s_.copy()
            if done or j == MAX_EP_STEPS-1:
                print('Ep: %i | %s | ep_r: %.1f | step: %i' % (i, '---' if not done else 'done', ep_r, j))
                break
    rl.save()

def eval():
    rl.restore()
    # env.render()
    # env.viewer.set_vsync(True)
    s = s_init.copy()
    while True:
        # env.render()
        a = rl.choose_action(s)
        # s, r, done = env.step(a)

# def step_env(action)

def plot_reward():
    import matplotlib.pyplot as plt
    # plt.plot(np.arange(len(reward_average)), reward_average)
    plt.ylabel('Average reward')
    plt.xlabel('Episode')
    plt.show()


if __name__ == '__main__':
    # init some parameters
    arg_list = parse_args()
    init_ros()
