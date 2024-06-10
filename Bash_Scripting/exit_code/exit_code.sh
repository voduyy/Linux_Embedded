#!/bin/bash 

package=noneexits
count=0
sudo apt install $package >> package_install_result.log
if [ $? == 0 ]
then 
    echo "This $package is being installed."
else    
    
    echo "[$(expr $count + 1)] Date:$(date)" >> package_install_failed.log
    echo "===> The installation of this $package is not complete" >> package_install_failed.log
fi