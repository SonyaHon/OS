#!/bin/bash
# Script compiles and starts lab needed. Look more in README.md file

# Number of lab to be launched
# Should clean up after
clean='false'
lab_num=1
while getopts "cn:a:" opt
do
case $opt in
c) echo "Cleaning afterwards..."
   clean="true"
   ;;
n) echo "Launching lab #${OPTARG}"
   lab_num=$OPTARG
   ;;
a) args+=("$OPTARG") 
   ;;   
esac
done

echo "------------------ Programm output ------------------"

lab_dir=$lab_num
lab_num+="/out"
make -C $lab_dir
./$lab_num $args

if [ "$clean" == "true" ];
then
    rm ./$lab_num
    if [ -f ./res_file ];
    then
        rm ./res_file
    fi 
fi
