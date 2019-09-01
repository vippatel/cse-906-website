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
Case : I L3 is inclusive of L2. L3 miss fills L3 & L2, L3 LRU Eviction causes L2 invalidation.
sphinx3  [Case-1-Incl] L2 Hits : 1803147 L2 Miss : 8398885 L3 Hits : 704992 L3 Miss : 7693893
bzip2    [Case-1-Incl] L2 Hits : 5217207 L2 Miss : 5440420 L3 Hits : 3994724 L3 Miss : 1445696
gcc      [Case-1-Incl] L2 Hits : 11506316 L2 Miss : 3104495 L3 Hits : 1739065 L3 Miss : 1365430
h264ref  [Case-1-Incl] L2 Hits : 1360757 L2 Miss : 987816 L3 Hits : 651559 L3 Miss : 336257
gromacs  [Case-1-Incl] L2 Hits : 3078775 L2 Miss : 352736 L3 Hits : 183280 L3 Miss : 169456
hmmer    [Case-1-Incl] L2 Hits : 1763486 L2 Miss : 1746279 L3 Hits : 1364676 L3 Miss : 381603
Case : II L3 is a NINE cache of L2. L3 miss fills L3 & L2, L3 LRU eviction has no impact on coressponding block in L2.
sphinx3  [Case-2-NINE] L2 Hits : 1932197 L2 Miss : 8269835 L3 Hits : 549184 L3 Miss : 7720651
bzip2    [Case-2-NINE] L2 Hits : 5260051 L2 Miss : 5397576 L3 Hits : 3951730 L3 Miss : 1445846
gcc      [Case-2-NINE] L2 Hits : 11581002 L2 Miss : 3029809 L3 Hits : 1663561 L3 Miss : 1366248
h264ref  [Case-2-NINE] L2 Hits : 1382949 L2 Miss : 965624 L3 Hits : 632041 L3 Miss : 333583
gromacs  [Case-2-NINE] L2 Hits : 3094787 L2 Miss : 336724 L3 Hits : 166265 L3 Miss : 170459
hmmer    [Case-2-NINE] L2 Hits : 1774443 L2 Miss : 1735322 L3 Hits : 1358978 L3 Miss : 376344
Case : III L3 is exclusive of L2. L3 miss fills L2. L2 Eviction fills L3. L3 hits invalidates L3 blocks, does not affect L2.
sphinx3  [Case-3-Excl] L2 Hits : 1932197 L2 Miss : 8269835 L3 Hits : 297399 L3 Miss : 7972436
bzip2    [Case-3-Excl] L2 Hits : 5260051 L2 Miss : 5397576 L3 Hits : 527144 L3 Miss : 4870432
gcc      [Case-3-Excl] L2 Hits : 11581002 L2 Miss : 3029809 L3 Hits : 274375 L3 Miss : 2755434
h264ref  [Case-3-Excl] L2 Hits : 1382949 L2 Miss : 965624 L3 Hits : 47709 L3 Miss : 917915
gromacs  [Case-3-Excl] L2 Hits : 3094787 L2 Miss : 336724 L3 Hits : 27698 L3 Miss : 309026
hmmer    [Case-3-Excl] L2 Hits : 1774443 L2 Miss : 1735322 L3 Hits : 24784 L3 Miss : 1710538
```

### Comparision : 

```
Comparision Analysis : Accross all 3 Cases. 

Case : I L3 is inclusive of L2. L3 miss fills L3 & L2, L3 LRU Eviction causes L2 invalidation.

Case : II L3 is a NINE cache of L2. L3 miss fills L3 & L2, L3 LRU eviction has no impact on coressponding block in L2.

Case : III L3 is exclusive of L2. L3 miss fills L2. L2 Eviction fills L3. L3 hits invalidates L3 blocks, does not affect L2.

bzip2    [Case-1-Incl] L2 Hits : 5217207 L2 Miss : 5440420 L3 Hits : 3994724 L3 Miss : 1445696
bzip2    [Case-2-NINE] L2 Hits : 5260051 L2 Miss : 5397576 L3 Hits : 3951730 L3 Miss : 1445846
bzip2    [Case-3-Excl] L2 Hits : 5260051 L2 Miss : 5397576 L3 Hits : 527144 L3 Miss : 4870432

gcc      [Case-1-Incl] L2 Hits : 11506316 L2 Miss : 3104495 L3 Hits : 1739065 L3 Miss : 1365430
gcc      [Case-2-NINE] L2 Hits : 11581002 L2 Miss : 3029809 L3 Hits : 1663561 L3 Miss : 1366248
gcc      [Case-3-Excl] L2 Hits : 11581002 L2 Miss : 3029809 L3 Hits : 274375 L3 Miss : 2755434

h264ref  [Case-1-Incl] L2 Hits : 1360757 L2 Miss : 987816 L3 Hits : 651559 L3 Miss : 336257
h264ref  [Case-2-NINE] L2 Hits : 1382949 L2 Miss : 965624 L3 Hits : 632041 L3 Miss : 333583
h264ref  [Case-3-Excl] L2 Hits : 1382949 L2 Miss : 965624 L3 Hits : 20698 L3 Miss : 944926

gromacs  [Case-1-Incl] L2 Hits : 3078775 L2 Miss : 352736 L3 Hits : 183280 L3 Miss : 169456
gromacs  [Case-2-NINE] L2 Hits : 3094787 L2 Miss : 336724 L3 Hits : 166265 L3 Miss : 170459
gromacs  [Case-3-Excl] L2 Hits : 3094787 L2 Miss : 336724 L3 Hits : 27698 L3 Miss : 309026

hmmer    [Case-1-Incl] L2 Hits : 1763486 L2 Miss : 1746279 L3 Hits : 1364676 L3 Miss : 381603
hmmer    [Case-2-NINE] L2 Hits : 1774443 L2 Miss : 1735322 L3 Hits : 1358978 L3 Miss : 376344
hmmer    [Case-3-Excl] L2 Hits : 1774443 L2 Miss : 1735322 L3 Hits : 24784 L3 Miss : 1710538

sphinx3  [Case-1-Incl] L2 Hits : 1803147 L2 Miss : 8398885 L3 Hits : 704992 L3 Miss : 7693893
sphinx3  [Case-2-NINE] L2 Hits : 1932197 L2 Miss : 8269835 L3 Hits : 549184 L3 Miss : 7720651
sphinx3  [Case-3-Excl] L2 Hits : 1932197 L2 Miss : 8269835 L3 Hits : 297399 L3 Miss : 7972436
```
### Full Assoc + LRU (L3 level Misses)

```
sphinx3  Cold Misses : 239377 Capacity Misses : 7621657 Total Misses : 7861034
bzip2    Cold Misses : 961097 Capacity Misses : 400304 Total Misses : 1361401
gcc      Cold Misses : 1000636 Capacity Misses : 369288 Total Misses : 1369924
h264ref  Cold Misses : 82213 Capacity Misses : 253667 Total Misses : 335880
gromacs  Cold Misses : 113538 Capacity Misses : 55830 Total Misses : 169368
hmmer    Cold Misses : 77255 Capacity Misses : 299769 Total Misses : 377024
```

### Inclusive Case + LRU (L3 level Misses)

```

```

### Disclaimer

Ignore the html and ./assets folder. 
It is not a part of the project.

Thanks.
