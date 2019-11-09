#!/bin/bash
# Set the number of robots
declare -i j

robots_num=$(rosparam get /control_terminal/robots_num)
		                                   
# spawn robots
for ((i=0; i<robots_num; i++))
do
    j=$i            
  
    rosrun task_allocation  task_allocation_node Robot${j}  __name:=Robot${j}_task_allocation &
               
#    rosrun gazebo_ros spawn_model -file $(rospack find gazebo_description)/models/Robot/model.sdf -sdf \
#                                  -model Robot${j} \
#                                  -x 0.0 -y 0.0 -z 0.0 &
done 
