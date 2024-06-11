#!/bin/bash
flag_exist= false
while [ -f $(pwd)/while_loop.sh ]
do 
    echo "File exists"
    flag_exist= true 
    break
done 
if [ "$flag_exist" == false ] #using boolean is check string to string, if 2 strings is equal then it corrects
then 
    echo "File don't exist" 
fi 
