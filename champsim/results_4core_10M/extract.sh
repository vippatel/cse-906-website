
result=0
for files in ./*-4core.txt; do
	((result++))	
	echo $result $files
	cat $files | grep -E "IPC|Accuracy|PREFETCH|PREFETCH REQUESTED|cummulative"
done

