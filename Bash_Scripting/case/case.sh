#!/bin/bash 
finish=0

while [ $finish -ne 1 ]
do 
    echo "What is your favorite sports?"
    echo "1.Football"
    echo "2.Basketball"
    echo "3.Volleyball"
    echo "4.Badminton"
    echo "5.Exit"
    
    read selection

    case $selection in 
        1) echo "I love football";;
        2) echo "I love Basketball";;
        3) echo "I love Volleyball";;
        4) echo "I love Badminton";; #;; like break
        5) finish=1;;
        *) echo "You pick wrong sports"
    esac #exit case 
done 