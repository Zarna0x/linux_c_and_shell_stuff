#!/bin/bash

echo -e "Enter username:\c"
read logname

cat /etc/passwd | grep "$logname" > /dev/null

if [ $? -eq 0 ]; then
  echo "Wait..."
else
  echo "User not found!"
  exit
fi

time=0

while true; do
  who | grep "$logname" > /dev/null
  if [ $? -eq 0 ]; then
    echo "$logname has logged in."
    if [ $time -ne 0 ]; then
      echo -e "$logname was $time minutes late logged in"
    fi
     exit
   else
     time=`expr $time + 1`
     sleep 60
   fi
done
