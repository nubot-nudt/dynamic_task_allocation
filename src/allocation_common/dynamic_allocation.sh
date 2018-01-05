#!/bin/bash			
# Get parameters
declare -i j
declare -i kill_num
robots_num=$(rosparam get /control_terminal/robots_num) 
kill_num=0                             

### spawn robots
for ((i=0; i<robots_num; i++))
do
    j=$i+1                                             

    rosrun world_model world_model_node ${j}  __name:=Robot${j}_world_model & PIDS[kill_num]=$!
    
    rosrun allocation  allocation_node ${j}  __name:=Robot${j}_allocation & PIDS[kill_num]=$!

    sleep 0.5
done 

