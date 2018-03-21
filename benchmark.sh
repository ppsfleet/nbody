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
INTERV="1"
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
			VAR=$( { ${TIME} -f "%e %P" ${COMMAND} -a ${ALGO} -n ${NBITER} -i ${INTERV} < ${var} > /dev/null; } 2>&1 )
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

while getopts a:n:i:t:f:hr OPT
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
				t)
						NBTIME=$OPTARG
						;;
				f)
						FILES=($OPTARG)
						;;
				h)
						echo "available parameters :"
						echo " -r: reset output file"
						echo " -a <bruteforce, barneshut>: algorithm, default: bruteforce"
						echo " -n <integer>: number of iteration, default: 2500"
						echo " -i <float>: interval between every iteration, default: 1"
						echo " -t <integer>: number of times the algorithm is executed, to calculated benchmark's mean"
						echo " -f <path>: path to folder containing datasets, default: datasets/*"
						exit 1
						;;
        \?)
            echo 'Invalid arguments'
            ;;
    esac
done

bench
