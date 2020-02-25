#!/bin/bash

## declare initial-states
declare -a initial_states=("1,2,3,7,4,5,6,8,0"
                          "2,8,1,3,4,6,7,5,0"
                          "1,2,3,4,5,6,7,8,0"
                          "2,8,1,3,4,6,7,5,0"
                          "4,1,3,2,5,6,7,8,0"
                          "1,2,3,4,5,6,7,8,0"
                          "8,6,7,2,5,4,3,0,1"
                          "6,4,7,8,5,0,3,2,1"
                          "2,1,3,8,0,4,6,7,5"
                          "1,3,4,8,6,2,7,0,5")

## declare goal-states
declare -a goal_states=("1,2,3,8,6,4,7,5,0"
                        "3,2,1,8,0,4,7,5,6"
                        "1,2,3,4,5,6,7,8,0"
                        "2,1,6,3,8,0,7,4,5"
                        "1,2,3,4,5,6,7,8,0"
                        "1,2,3,4,8,5,7,6,0"
                        "1,2,3,4,5,6,7,8,0"
                        "1,2,3,4,5,6,7,8,0"
                        "1,2,3,4,5,6,7,8,0"
                        "1,2,3,8,0,4,7,6,5")

# get length of initial-stats
arraylength=${#initial_states[@]}

# use for loop to read all values and indexes
for (( i=1; i<${arraylength}+1; i++ ));
do
  echo $i " / " ${arraylength} " : " ${initial_states[$i-1]} " : " ${goal_states[$i-1]}

  # a_star
  ./../../puzzle -problem 8-puzzle -algo a_star -mode na -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # ida_star
  ./../../puzzle -problem 8-puzzle -algo ida_star -mode na -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # bfs
  ./../../puzzle -problem 8-puzzle -algo bfs -mode na -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # bfs [optimized]
  ./../../puzzle -problem 8-puzzle -algo bfs -mode optimized -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # bfs [greedy]
  ./../../puzzle -problem 8-puzzle -algo bfs -mode greedy -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # bfs [bi-directional]
  ./../../puzzle -problem 8-puzzle -algo bfs -mode bi-directional -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # dfs [recursive]
  ./../../puzzle -problem 8-puzzle -algo dfs -mode recursive -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # dfs [stack-based]
  ./../../puzzle -problem 8-puzzle -algo dfs -mode stack-based -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # dls
  ./../../puzzle -problem 8-puzzle -algo dls -mode na -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # dls [bi-directional]
  ./../../puzzle -problem 8-puzzle -algo dls -mode bi-directional -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # ids
  ./../../puzzle -problem 8-puzzle -algo ids -mode na -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  # ids [bi-directional]
  ./../../puzzle -problem 8-puzzle -algo ids -mode bi-directional -heu manhattan -initial ${initial_states[$i-1]} -goal ${goal_states[$i-1]} -print_path false
  echo ""

  echo "~~~~~~~~~~~~~~~~~~~~~~~~~<>~~~~~~~~~~~~~~~~~~~~~~~~~"
done
