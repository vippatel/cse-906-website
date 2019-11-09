trace_file="./trace_list_source_file"
processor_file="./processor_list_file"

traces=`cat $trace_file`
processors=`cat $processor_file`

for processor in $processors; do
	for trace in $traces; do
		./run_champsim.sh $processor 1 10 $trace
	done
done
