### Pre-requisite.

Install gcc/g++ on linux.

### Run file :

```
sudo g++ -O3 -std=c++17 case1_code.cpp -o trace.out
./trace.out <name-prefix-trace> config.txt <#number-of-files>
```
```
<name-prefix-trace> -> prefix file-name of trace.
<#number-of-files> -> file numbers of trace (eg. 2 for gcc_trace) 
```

### Run Example :
```
sudo g++ -std=c++2a -O3 case1_code.cpp -o trace_reader.out
time ./trace_reader.out gcc.log_l1misstrace config.txt 2
```

```Please check Assignment.txt and Clarification.txt.```

### Working : 


Please fill up code as per case here. 

[Cache_miss + Replacement](https://github.com/codersguild/cse-906-website/blob/ec7c1ea7268475e0e3c020b7455ffb7f6d0a0f3d/code.cpp#L156)

```cpp
if(l2_hit == false && l3_hit == false) {
    // Need to write logic here.
}
 ```
 
### Disclaimer

Ignore the html and ./assets folder. 
It is not a part of the project.

Thanks.
