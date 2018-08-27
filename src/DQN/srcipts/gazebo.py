#!/usr/bin/env python

import rospy
from std_msgs.msg import String

from gym import spaces
import numpy as np

# environment for gazebo
class GazeboEnv:
    def __init__(self):
        rospy.init_node('dqn_ros', anonymous=True)
        rospy.Subscriber('chatter', String, self.gazebo_callback)

        self.is_gazebo_callback = False
        self.is_reward_callback = False
        self.is_observation_callback = False
        self.taskNum = 0
        self.teamNum = 0
        self.adversariesNum = 0

        self.action_space = spaces.Discrete(1)
        self.observation_space = spaces.Box(low=-np.inf, high=+np.inf, shape=(1,), dtype=np.float32)
        self.action_space_n = []
        self.observation_space_n = []
        self.action_ID = 0
        self.observation_ID = 0


    # start the spin for the callback
    @staticmethod
    def start_spin():
        rospy.spin()

    def reset(self):
        obs_n = self.observation_space
        return obs_n

    # execute the action in the gazebo world
    def step(self, action):
        print('choose the task', action)

    # function for callback
    def gazebo_callback(self, data):
        if not self.is_gazebo_callback:
            rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)

            self.is_gazebo_callback= True
            self.teamNum = 4
            self.taskNum = 10

            # action_space
            self.action_space = spaces.Discrete(self.taskNum + 1)
            # observation_space
            self.observation_space = spaces.Box(low=-np.inf, high=+np.inf, shape=(self.teamNum + self.taskNum,), dtype=np.float32)

            for i in range(self.teamNum)
                self.action_space_n.append(self.action_space)
                self.observation_space_n.append(self.observation_space)

    def get_observation(self):
        return self.observation_space_n[self.observation_ID], self.observation_ID

    def set_action(self, action, action_id):
        self.action_space_n[action_id]= action

