#!/bin/bash

if [ -d /etc/pacman ]
then 
    sudo pacman -Syu
fi

if [ -d /etc/apt ]
then 
    sudo apt update
   #sudo apt dist-upgrade
fi 