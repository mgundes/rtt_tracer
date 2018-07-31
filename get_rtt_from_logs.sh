#!/bin/bash

usage_f() {
    echo "$0 <minimum_rtt_time_ms> <file_path>"
}

if [ "$#" != 2 ]; then
    usage_f
    exit 1
fi

MIN=$1
FILE="$2"

if [ ! -r $FILE ]; then
    echo "File does not exist or not readable!"
    exit 1
fi

if [ "$MIN" -lt 3 ]; then
    echo "Choose more than 3 miliseconds!"
    exit 1
fi

while read LINE
do
    if echo $LINE | grep "RTT: " > /dev/null
    then
        time=`echo $LINE | awk -F "," '{print $3}' | awk -F " " '{print $2}'`
        if [ "$time" -gt "$MIN" ]
        then
            echo "$LINE"
        fi
    fi
done < $FILE
