
result=0
for files in ./*-1core.txt; do
	((result++))
	echo $result $files
	cat $files | grep -E "IPC|Accuracy|PREFETCH|PREFETCH REQUESTED|cummulative" | grep -o -E "[0-9]+\.[0-9]*"
done

