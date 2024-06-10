#!/bin/bash

my_name="Duy" 

echo "hello world $my_name"
echo "this is my path: $(pwd)"
echo "Date: $(date)"
echo "$(expr 30 - 10)"
variables=$(expr 100 \* 4)

if [ -f gpio.c ]
then 
    echo "File exists"
else 
    echo "Files don't exist"
fi 

command=/usr/bin/htop

if command -v $command
then 
    echo "There is a command"
else 
    echo "There is not any command like this"
    sudo apt-get update && sudo apt install -y htop
fi
$command
