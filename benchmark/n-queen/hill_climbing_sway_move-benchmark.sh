#!/bin/bash

# use for loop to run each case for 500 times
counter=1
while [ $counter -le 500 ]
do
  ./../../puzzle -problem n-queen -algo hill-climbing -mode sideways-move -board_dim 10 -mx_sideways_move 10 -print_path false
  ((counter++))
  sleep 1
done
