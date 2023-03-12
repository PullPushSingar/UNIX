#!/bin/sh


for file in *
do
        if expr "$file" : '.* ' > /dev/null
        then
                spaces=`echo $file | sed 's/ /_/g'`
                mv "$file" "$spaces"
                echo "nazwa zostala zmieniona"
        else
                echo "nazwa nie zostala zmieniona"
                fi
done