#!/bin/bash

sudo apt-get install sysvbanner
banner cFounder
command=$1
EXISTS=`which $command`

if [ ! -z "$EXISTS"  ]; then
  echo "command exists here: $EXISTS"
else
   echo "command doesnot exists"
   echo -e "Do you want install it? [y/n]:\c"
   read opt 
   if [ $opt == "y" ]; then
     echo -e "[*] Installing $command ..."
     APT_EXISTS=`sudo apt-get install $command`
     echo -e "package $command succesfully installed and its location is: $(which $command)"
     # check if package exists
    fi
fi
