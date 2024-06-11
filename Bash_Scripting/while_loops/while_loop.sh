#!/bin/bash

my_var=1

while [ $my_var -le 10 ]
do 
    echo $my_var
    my_var=$(( $my_var + 1 )) #create new version of my_var, like create new variables and assign value to it
    sleep 0.5 #sleep 0.5s
done