trace_file="./trace_list_multicore"
processor_file="./processor_list_file"

traces=`cat $trace_file`
processors=`cat $processor_file`


run=0
for trace in $traces; do
	for processor in $processors; do
		((run++))
		echo $trace
	done
done
