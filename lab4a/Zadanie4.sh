#!/bin/sh

if [ "$#" -ne "1" ]
then
        echo "Pass only one argument"
        exit 1

fi

endofargument="$1"
mkdir -p  "$HOME/.arch"
for file in `ls`
do

        if expr $file : '.*.'$endofargument'$' > /dev/null
        then
                newfilename=`echo $file | sed  's/'$endofargument/_arch\$1\/`
                cp -p $file  $HOME/.arch/"$newfilename"

        fi
done
#end
#Zadanie uruchomino,sprawdzono,przetestowano na serwerze diablo.
