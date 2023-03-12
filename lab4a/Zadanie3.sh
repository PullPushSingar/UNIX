
#!/bin/sh


for argument in "$@"
do
	endOfArgument=`expr $argument : ".*\(.txt\)$"`

	if  test "$endOfArgument" = ".txt"
	then
        	newName=`echo $argument | sed  's/.txt/_org.txt/'`
        	mv   $argument "$newName"
        	echo name was changed
	else
        	echo Argument is not \".txt\" file !!!
	fi

done

#zadanie uruchomiono,sprawdzono,przetestowano na serwerze diablo

#UWAGA
# Z powodu awarii diablo(diablo wznowiło prace w dzień laboraorium)
# Zadanie zostało napisane na panamincie. Prowadzący uznał poprawność jednak zadanie
#Zostało napisane jeszcze raz w taki sposób , aby działało na diablo

