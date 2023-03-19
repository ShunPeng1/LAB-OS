#!usr/bin/bash
#file calc.sh

touch calc_data.txt
ANS=$(< calc_data.txt)
declare -a HIST
len=0


Calculate(){
#$1 = int , $2 = operator , $3 = int, 
	#echo "$1"
	#echo "$2"
	#echo "$3"

	case "$2" in

  	"+")
		ANS=$(echo " $1+$3" | bc)
    		echo $ANS
    	;;

  	"-")
   		ANS=$(echo " $1-$3" | bc)
    		echo $ANS
    	;;

  	"x")
		ANS=$(echo " $1*$3" | bc)
    		echo $ANS
    	;;

  	"/")
		if [ $3 -eq 0 ]; then
			echo "MATH ERROR"
		return
		fi

		ANS=$(echo "scale=2; $1/$3" | bc)
    		echo $ANS
    	;;

  	"%")
	    	ANS=$(echo " $1-$3" | bc)
    		echo $ANS
    	;;
	esac

	echo "$ANS" > calc_data.txt

}

History(){

	low=$(echo "$len-5" | bc)
	lower=$(( $low > 0 ? $low : 0 ))
	#echo "$len  $low  $lower"
	for (( i=$lower; i<$len; i++ )); do
		echo   "${HIST[$i]}"
	done

}

Extract(){

	read -p ">> "  input

	if [ "$input" = "HIST" ]; then
		History
		return
	fi

	if [ "$input" = "EXIT" ]; then
		kill $$
	fi

	regex='^([0-9]+|ANS)[ ]([+-X/%])[ ]([0-9]+|ANS)$'

	if [[ "$input" =~ $regex ]]; then

		first=${BASH_REMATCH[1]}
		operator=${BASH_REMATCH[2]}
		second=${BASH_REMATCH[3]}

		if [ "$first" = "ANS" ]; then
			first=$ANS
		fi

		if [ "$second" = "ANS" ]; then
			second=$ANS
		fi

		Calculate "$first" "$operator" "$second"

		# save to history
		HIST[$len]="${BASH_REMATCH[1]} ${BASH_REMATCH[2]} ${BASH_REMATCH[3]} = $ANS"
		len=$(echo "$len+1"|bc)


	else
		echo "SYNTAX ERROR"
	fi


}



while [[ 1 ]] ; do
	Extract
done
