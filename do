#!/bin/bash
# Script compiles and starts lab needed. Look more in README.md file

# Number of lab to be launched
lab_num=$1 
# Should clean up after
clean=$2
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
