  GNU nano 6.3               C:\Users\huber\Desktop\0STUDIA\Raporty Unix\lab4a\zadanie5.sh #!/bin/sh  if [ "$#" -ne "1" ] then         echo "Pass only one argument"         exit 1  fi  endofargument="$1"  mkdir -p  "$HOME/.arch"  for file in `ls` do         if expr $file : '.*.'$endofargument'$' > /dev/null         then                 bnexecution=`basename $file $endofargument`                 newname=`echo "$bnexecution"_arch"$endofargument"`                 cp -p $file $HOME/.arch/"$newname"          fi done #end #Zadanie uruchomino,sprawdzono,przetestowano na serwerze diablo#!/bin/sh

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
                bnexecution=`basename $file $endofargument`
                newname=`echo "$bnexecution"_arch"$endofargument"`
                cp -p $file $HOME/.arch/"$newname"

        fi
done
#end
#Zadanie uruchomino,sprawdzono,przetestowano na serwerze diablo
