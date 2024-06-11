#!/bin/bash
release_package=/etc/os-release
error_log=error.log
result_log=output.log

create_files_log()
{
    if [ -e $error_log ]  #is exist
    then     
        echo "File exists"
        if [ -w $error_log ] #check permission write
        then 
            echo "This $error_log can write"
        else 
            echo "Giving permission write for this $error_log file"
            chmod a+w $error_log
        fi
    else 
        touch $error_log
        chmod a+w $error_log
    fi 

    if  [ -e $result_log ] #is exist
    then     
        echo "File exists"
        if [ -w $result_log ] #check permission write
        then 
            echo "This $result_log can write"
        else 
            echo "Giving permission write for this $result_log file"
            chmod a+w $result_log
        fi
    else 
        touch $result_log
        chmod a+w $result_log
    fi 
}
check_exit_status()
{
    if [ $? -ne 0 ]
    then 
        echo "This is Arch"
        echo "Check error logs"
    else 
        echo "Successfully, check output logs"
    fi
  
}
create_files_log

if grep -q "Arch" $release_package #grep -q: find in slient no message
then 
    for log_files in $result_log $error_log; do echo "Started at: $(date)" >> $log_files; done
    sudo pacman -Syu 1>> $result_log 2>> $error_log   
    check_exit_status
    for log_files in $result_log $error_log; do echo "Finished at: $(date)" >> $log_files; done


fi 

if grep -q "Ubuntu" $release_package || grep -q "Debian" $release_package
then 
    for log_files in $result_log $error_log; do echo "Started at: $(date)" >> $log_files; done
    sudo apt update -y 1>> $result_log 2>> $error_log  
    check_exit_status
    for log_files in $result_log $error_log; do echo "Finished at: $(date)" >> $log_files; done
fi 