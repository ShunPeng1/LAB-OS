input1 := sum_serial.c
output1 := sum_serial
input2 := sum_multi-thread.c
output2 := sum_multi-thread


all: 
	gcc -o ${output1} ${input1}
	gcc -o ${output2} ${input2}


${output1}: $(input1)
	gcc -o ${output1} ${input1}

clean: 
	rm -f ${output1}
	rm -f ${output2}