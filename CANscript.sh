#!/bin/bash

echo "Hello User!"

main () {
  sudo ip link set can0 type can bitrate 500000
  read -p "What CAN Function would you like to perform? (1-Read, 2-Write, 3-Neither)" number
  if [ $number -eq 1 ];
  then
    echo "You have selected the Read Function!"
    candump can0
  fi
  if [ $number -eq 2 ];
  then
    echo "You have selected the Write Function!"
    can0 123#1122334455667788
  fi
  if [ $number -eq 3 ];
  then
    echo "You have selected Neither!"
  fi
}

main
