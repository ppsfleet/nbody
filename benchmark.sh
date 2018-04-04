#!/bin/bash

# prerequis : install time

# mesure time of execution of nbody on every file in $FILES
# each $FILE is executed $NBTIME, then the mean of execution time is calculated and outputed in $OUTPUT
# output format : $FILE $ALGO $NBITER $INTERV $NBTIME $MEANPRCT% $MEANTIME
COMMAND='bin/nbody'
OUTPUT='result.csv'
NBTIME=10
FILES=(datasets/*)
TIME=$(which time)
ALGO="bruteforce"
NBITER="2500"
INTERV="0.01"
IP="127.0.0.1"
PORT="3001"
THRESHOLD="0.5"
OUTPUTOPT="false"
SEND="1"
declare SUMTIME=0

bench(){
	for var in "${FILES[@]}"
	do
		# keep track of the process
		echo "Running test on ${var} with ${ALGO}"
		#reset $SUMTIME, $SUMPRCT, $MEANPRCT and $MEANTIME
		SUMTIME=0
		MEANTIME=0
		MEANPRCT=0
		SUMPRCT=0
		# run the programm NBTIME times then do the mean
		for ((i = 1; i <= NBTIME ; i++))
		do
			if [ $OUTPUTOPT == "false" ]
			then
				VAR=$( { ${TIME} -f "%e %P" ${COMMAND} -a ${ALGO} -n ${NBITER} -i ${INTERV} -s ${IP} -p ${PORT} -u ${SEND} -t ${THRESHOLD} < ${var} > /dev/null; } 2>&1 )
			else
				VAR=$( { ${TIME} -f "%e %P" ${COMMAND} -a ${ALGO} -n ${NBITER} -i ${INTERV} -o -u ${SEND} -t ${THRESHOLD} < ${var} > /dev/null; } 2>&1 )
			fi

			# echo ${VAR}
			VAR=${VAR//%}
			IFS=' '        # space is set as delimiter
			read -ra ARR <<<"$VAR"
			SUMTIME=$( bc -l <<< "${SUMTIME}+${ARR[0]}" )
			SUMPRCT=$( bc -l <<< "${SUMPRCT}+${ARR[1]}" )
		done;
		MEANTIME=$( bc -l <<< "scale=3; ${SUMTIME}/${NBTIME}" )
		MEANPRCT=$( bc -l <<< "scale=3; ${SUMPRCT}/${NBTIME}" )
		# store the mean in output file
		echo $var $ALGO $NBITER $INTERV $NBTIME $MEANPRCT"%" $MEANTIME >> ${OUTPUT}
	done;
}

while getopts a:n:i:T:f:s:p:u:t:ohr OPT
do
    case "$OPT" in
				r)
						# reset output file
						> ${OUTPUT}
						;;
        a)
						if [[ "$OPTARG" == "barneshut" || "$OPTARG" == "bruteforce" ]]
						then
            	ALGO=$OPTARG
						else
							echo "invalid arlgorithm, try barneshut or bruteforce"
							exit 1
						fi
            ;;
        n)
            NBITER=$OPTARG
            ;;
        i)
            INTERV=$OPTARG
            ;;
				T)
						NBTIME=$OPTARG
						;;
				f)
						FILES=($OPTARG)
						;;
				s)
						IP=($OPTARG)
						;;
				f)
						PORT=($OPTARG)
						;;
				o)
						OUTPUTOPT="true"
						;;
				u)
						SEND=($OPTARG)
						;;
				t)
						THRESHOLD=($OPTARG)
						;;
				h)
						echo "available parameters :"
						echo " -r: reset output file"
						echo " -a <bruteforce, barneshut>: algorithm, default: bruteforce"
						echo " -n <integer>: number of iteration, default: 2500"
						echo " -i <float>: interval between every iteration, default: 1"
						echo " -s <value>: for setting the ip of the server, default : 127.0.0.1"
						echo " -p <value>: for setting the port of the server, default : 3001"
						echo " -T <integer>: number of times the algorithm is executed, to calculated benchmark's mean"
						echo " -f <path>: path to folder containing datasets, default: datasets/*"
						echo " -t <float>: for setting the threshold of barneshut, default : 0.5"
	          echo " -o : for setting the output method, default : socket"
	          echo " -u <integer>: for setting the interval between each output of particle (for exemple, 3 : for 1 particle out of 3), default : 1 (all particles outputed)"
						exit 1
						;;
        \?)
            echo 'Invalid arguments'
            ;;
    esac
done

bench
