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

```
[1 for case]
sudo ./trace_reader.out bzip2.log_l1misstrace config.txt 2 > outfile_bzip_1.txt
sudo ./trace_reader.out gcc.log_l1misstrace config.txt 2 > outfile_gcc_1.txt
tail -2 outfile_bzip_1.txt
tail -2 outfile_gcc_1.txt
```

### Working : 


Please fill up code as per case here. 

[Cache_miss + Replacement](https://github.com/codersguild/cse-906-website/blob/ec7c1ea7268475e0e3c020b7455ffb7f6d0a0f3d/code.cpp#L156)

```cpp
if(l2_hit == false && l3_hit == false) {
    // Need to write logic here.
}
 ```
 ### Output : 
 
```
Case : I
sphinx3 [Case-1-Incl] L2 Hits : 1803147 L2 Miss : 8398885 L3 Hits : 704992 L3 Miss : 7693893
bzip2 [Case-1-Incl] L2 Hits : 5217207 L2 Miss : 5440420 L3 Hits : 3994724 L3 Miss : 1445696
gcc [Case-1-Incl] L2 Hits : 11506316 L2 Miss : 3104495 L3 Hits : 1739065 L3 Miss : 1365430
h264ref [Case-1-Incl] L2 Hits : 1360757 L2 Miss : 987816 L3 Hits : 651559 L3 Miss : 336257
gromacs [Case-1-Incl] L2 Hits : 3078775 L2 Miss : 352736 L3 Hits : 183280 L3 Miss : 169456
hmmer [Case-1-Incl] L2 Hits : 1763486 L2 Miss : 1746279 L3 Hits : 1364676 L3 Miss : 381603
Case : II
sphinx3 [Case-2-NINE] L2 Hits : 1932197 L2 Miss : 8269835 L3 Hits : 549184 L3 Miss : 7720651
bzip2 [Case-2-NINE] L2 Hits : 5260051 L2 Miss : 5397576 L3 Hits : 3951730 L3 Miss : 1445846
gcc [Case-2-NINE] L2 Hits : 11581002 L2 Miss : 3029809 L3 Hits : 1663561 L3 Miss : 1366248
h264ref [Case-2-NINE] L2 Hits : 1382949 L2 Miss : 965624 L3 Hits : 632041 L3 Miss : 333583
gromacs [Case-2-NINE] L2 Hits : 3094787 L2 Miss : 336724 L3 Hits : 166265 L3 Miss : 170459
hmmer [Case-2-NINE] L2 Hits : 1774443 L2 Miss : 1735322 L3 Hits : 1358978 L3 Miss : 376344
Case : III
sphinx3 [Case-3-Excl] L2 Hits : 1932197 L2 Miss : 8269835 L3 Hits : 311223 L3 Miss : 7958612
bzip2 [Case-3-Excl] L2 Hits : 5260051 L2 Miss : 5397576 L3 Hits : 422962 L3 Miss : 4974614
gcc [Case-3-Excl] L2 Hits : 11581002 L2 Miss : 3029809 L3 Hits : 15682 L3 Miss : 3014127
h264ref [Case-3-Excl] L2 Hits : 1382949 L2 Miss : 965624 L3 Hits : 20698 L3 Miss : 944926
gromacs [Case-3-Excl] L2 Hits : 3094787 L2 Miss : 336724 L3 Hits : 16244 L3 Miss : 320480
hmmer [Case-3-Excl] L2 Hits : 1774443 L2 Miss : 1735322 L3 Hits : 41804 L3 Miss : 1693518
```

 
### Disclaimer

Ignore the html and ./assets folder. 
It is not a part of the project.

Thanks.
