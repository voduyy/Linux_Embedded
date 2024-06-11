#!/bin/bash 
package_at=/usr/bin/at
if [ -e $package_at ]
then 
    echo "There is at command, path to command $package_at"
else 
    echo "Don't have at command"
    sudo apt install -y at 1>>log_files 2>>errors.log
fi