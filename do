#!/bin/bash
# Script compiles and starts lab needed. Look more in README.md file

# Number of lab to be launched
# Should clean up after
clean='false'
lab_num=1
while getopts "cn:" opt
do
case $opt in
c) echo "Cleaning afterwards..."
   clean="true"
   ;;
n) echo "Launching lab #${OPTARG}"
   lab_num=$OPTARG
   ;;
esac
done

lab_num+="/out"
if [ -f $lab_num ]; 
then
    ./$lab_num 
else
    cd ./$1/
    make
    cd ../
    ./$lab_num
fi

if [ "$clean" == "true" ];
then
    rm ./$lab_num
    if [ -f ./res_file ];
    then
        rm ./res_file
    fi 
fi
