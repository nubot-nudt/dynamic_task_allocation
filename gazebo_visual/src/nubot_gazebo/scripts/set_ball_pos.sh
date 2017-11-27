#!/bin/bash
football_name=$(rosparam get /football/name)

### Generate random number. Input:a b Output: random number in [a,b]
function rand
{
    d=$1
    c=$2-$1+1
    pos=$RANDOM
    let "pos = pos % c + d"
    echo $pos
}

while [ true ];
do
    echo "Input ball position number. c* is corner"
    echo "-----------------------------------------"
    echo "| c1                                  c3|"
    echo "| 1                  4                 7|"
    echo "| 2                  5                 8|"
    echo "| 3                  6                 9|"
    echo "| c2                                  c4|"
    echo "-----------------------------------------"
    read input
    case ${input} in
	    1)
            rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: -6.0
                  y: 3.0
                  z: 0.0
              reference_frame: ''"
              ;;
        2)
            rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: -6.0
                  y: 0.0
                  z: 0.0
              reference_frame: ''"
              ;;
        3)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: -6.0
                  y: -3.0
                  z: 0.0
              reference_frame: ''"
              ;;   
        4)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 0.0
                  y: 3.0
                  z: 0.0
              reference_frame: ''"
              ;;                       
        5)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 0.0
                  y: 0.0
                  z: 0.0
              reference_frame: ''"
              ;;  
        6)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 0.0
                  y: -3.0
                  z: 0.0
              reference_frame: ''"
              ;;   
        7)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 6.0
                  y: 3.0
                  z: 0.0
              reference_frame: ''"
              ;;   
        8)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 6.0
                  y: 0.0
                  z: 0.0
              reference_frame: ''"
              ;;   
        9)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 6.0
                  y: -3.0
                  z: 0.0
              reference_frame: ''"
              ;;   
        c1)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: -8.8
                  y: 5.8
                  z: 0.0
              reference_frame: ''"
              ;;   
        c2)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: -8.8
                  y: -5.8
                  z: 0.0
              reference_frame: ''"
              ;; 
        c3)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 8.8
                  y: 5.8
                  z: 0.0
              reference_frame: ''"
              ;; 
        c4)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: 8.8
                  y: -5.8
                  z: 0.0
              reference_frame: ''"
              ;;   
        *)
             rosservice call /gazebo/set_model_state "model_state: 
              model_name: '${football_name}'
              pose:
                position:
                  x: $(rand -8 8)
                  y: $(rand -5 5)
                  z: 0.0
              reference_frame: ''"
              ;;                                                                                               
    esac
done
