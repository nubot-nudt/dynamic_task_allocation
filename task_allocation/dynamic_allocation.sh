#!/bin/bash			
source devel/setup.bash
# Get parameters and init
declare -i j
declare -i kill_num
agent_num=4 
kill_num=0                             

### spawn cyan robots
for ((i=0; i<agent_num; i++))
do
    j=$i+1                                             

    rosrun world_model world_model_node ${j}  __name:=Agent${j}_world_model & PIDS[kill_num]=$!
    
    rosrun allocation  allocation_node ${j}  __name:=Agent${j}_allocation & PIDS[kill_num]=$!

    sleep 0.5
done 

# kill thoes background processes
trap 'kill ${PIDS[*]}' SIGINT
wait

