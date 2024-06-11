#!/bin/bash

release_package=/etc/os-release

if grep -q "Arch" $release_package #grep -q: find in slient no message
then 
    sudo pacman -Syu
fi 

if grep -q "Ubuntu" $release_package || grep -q "Debian" $release_package
then 
    sudo apt update
fi 