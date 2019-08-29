### Pre-requisite.

Install gcc/g++ on linux.

### Run file :

```
sudo g++ -O3 -std=c++17 code.cpp -o trace.out
./trace.out <name-prefix-trace> config.txt <#number-of-files>
```
```
<name-prefix-trace> -> prefix file-name of trace.
<#number-of-files> -> file numbers of trace (eg. 2 for gcc_trace) 
```

### Run Example :
```
sudo g++ -std=c++2a -O3 code.cpp -o trace_reader.out
time ./trace_reader.out gcc.log_l1misstrace config.txt 2
```

```Please check Assignment.txt and Clarification.txt.```


### Disclaimer

Please don't share it. Ask me before-hand. Ignore the html and ./assets folder. 
It is not a part of the project.

Thanks.
