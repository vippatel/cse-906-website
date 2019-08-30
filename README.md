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
 ### Output : 
 
 ```
 Case - 1 : [INFO] L2 Hits : 179342, L2 Miss : 6534297, L3 Hits : 181129, L3 Miss : 6353168
 Case - 2 : [INFO] L2 Hits : 1319934, L2 Miss : 5393705, L3 Hits : 50366, L3 Miss : 5343339
  ```
 
 [LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 251, TAG : 42
L3 HIT : 251, 14, 21
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2767908
L3 MISS -> SET : 4, TAG : 1383954
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275515703296
L3 MISS -> SET : 0, TAG : 137757851648
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 181355675905
L3 MISS -> SET : 1025, TAG : 90677837952
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 208, TAG : 42
L3 HIT : 208, 9, 21
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2764634
L3 MISS -> SET : 4, TAG : 1382317
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 181085339905
L3 MISS -> SET : 1025, TAG : 90542669952
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 155, TAG : 42
L3 MISS -> SET : 155, TAG : 21
L2 MISS -> SET : 0, TAG : 1103810799056
L3 MISS -> SET : 0, TAG : 551905399528
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 0, TAG : 3962236
L3 MISS -> SET : 0, TAG : 1981118
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 180928446721
L3 MISS -> SET : 1025, TAG : 90464223360
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 117, TAG : 42
L3 MISS -> SET : 117, TAG : 21
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2759111
L3 MISS -> SET : 1028, TAG : 1379555
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259828482049
L3 MISS -> SET : 1025, TAG : 129914241024
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 91, TAG : 42
L3 MISS -> SET : 91, TAG : 21
L2 MISS -> SET : 0, TAG : 1103810799108
L3 MISS -> SET : 0, TAG : 551905399554
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2757558
L3 MISS -> SET : 4, TAG : 1378779
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 180673904897
L3 MISS -> SET : 1025, TAG : 90336952448
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 50, TAG : 42
L3 MISS -> SET : 50, TAG : 21
L2 MISS -> SET : 0, TAG : 4299171296
L3 MISS -> SET : 0, TAG : 2149585648
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2755061
L3 MISS -> SET : 1028, TAG : 1377530
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 180486013185
L3 MISS -> SET : 1025, TAG : 90243006592
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41575283425280
L3 MISS -> SET : 0, TAG : 20787641712640
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 6, TAG : 42
L3 HIT : 6, 5, 21
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2752334
L3 MISS -> SET : 4, TAG : 1376167
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 180248379649
L3 MISS -> SET : 1025, TAG : 90124189824
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 961, TAG : 41
L3 MISS -> SET : 1985, TAG : 20
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 0, TAG : 3964540
L3 MISS -> SET : 0, TAG : 1982270
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 179990954241
L3 MISS -> SET : 1025, TAG : 89995477120
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41575283425280
L3 MISS -> SET : 0, TAG : 20787641712640
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 916, TAG : 41
L3 MISS -> SET : 1940, TAG : 20
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2744050
L3 MISS -> SET : 4, TAG : 1372025
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 179797033217
L3 MISS -> SET : 1025, TAG : 89898516608
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 865, TAG : 41
L3 MISS -> SET : 1889, TAG : 20
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2741742
L3 MISS -> SET : 4, TAG : 1370871
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275512295424
L3 MISS -> SET : 0, TAG : 137756147712
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259652321281
L3 MISS -> SET : 1025, TAG : 129826160640
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 808, TAG : 41
L3 HIT : 1832, 5, 20
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2738183
L3 MISS -> SET : 1028, TAG : 1369091
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 179385073921
L3 MISS -> SET : 1025, TAG : 89692536960
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 776, TAG : 41
L3 HIT : 1800, 4, 20
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 0, TAG : 275512295424
L3 MISS -> SET : 0, TAG : 137756147712
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259648126977
L3 MISS -> SET : 1025, TAG : 129824063488
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 750, TAG : 41
L3 HIT : 1774, 3, 20
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 2733645
L3 MISS -> SET : 1028, TAG : 1366822
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 179106283777
L3 MISS -> SET : 1025, TAG : 89553141888
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 463, TAG : 60
L3 HIT : 463, 15, 30
L2 MISS -> SET : 0, TAG : 4299171296
L3 MISS -> SET : 0, TAG : 2149585648
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 379321
L3 MISS -> SET : 1028, TAG : 189660
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275513344000
L3 MISS -> SET : 0, TAG : 137756672000
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 24762450177
L3 MISS -> SET : 1025, TAG : 12381225088
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41644002902016
L3 MISS -> SET : 0, TAG : 20822001451008
[LRU Victim] Cache miss in index : 0, 15
L2 HIT : 236, 4, 7
L2 MISS -> SET : 0, TAG : 1103810799072
L3 MISS -> SET : 0, TAG : 551905399536
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3956736
L3 MISS -> SET : 4, TAG : 1978368
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275534053376
L3 MISS -> SET : 0, TAG : 137767026688
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259686137857
L3 MISS -> SET : 1025, TAG : 129843068928
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42932493090816
L3 MISS -> SET : 0, TAG : 21466246545408
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 475, TAG : 60
L3 MISS -> SET : 475, TAG : 30
L2 MISS -> SET : 0, TAG : 4299171596
L3 MISS -> SET : 0, TAG : 2149585798
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3962880
L3 MISS -> SET : 4, TAG : 1981440
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275533529088
L3 MISS -> SET : 0, TAG : 137766764544
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259715497985
L3 MISS -> SET : 1025, TAG : 129857748992
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42915313221632
L3 MISS -> SET : 0, TAG : 21457656610816
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 396, TAG : 60
L3 HIT : 396, 12, 30
L2 MISS -> SET : 0, TAG : 4299171596
L3 MISS -> SET : 0, TAG : 2149585798
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3963328
L3 MISS -> SET : 4, TAG : 1981664
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275533529088
L3 MISS -> SET : 0, TAG : 137766764544
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259744858113
L3 MISS -> SET : 1025, TAG : 129872429056
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42915313221632
L3 MISS -> SET : 0, TAG : 21457656610816
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 402, TAG : 60
L3 HIT : 402, 5, 30
L2 MISS -> SET : 0, TAG : 4299171596
L3 MISS -> SET : 0, TAG : 2149585798
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3963584
L3 MISS -> SET : 4, TAG : 1981792
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275533529088
L3 MISS -> SET : 0, TAG : 137766764544
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259392536577
L3 MISS -> SET : 1025, TAG : 129696268288
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42915313221632
L3 MISS -> SET : 0, TAG : 21457656610816
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 494, TAG : 60
L3 MISS -> SET : 494, TAG : 30
L2 MISS -> SET : 0, TAG : 4299171596
L3 MISS -> SET : 0, TAG : 2149585798
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3963840
L3 MISS -> SET : 4, TAG : 1981920
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275533529088
L3 MISS -> SET : 0, TAG : 137766764544
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259409313793
L3 MISS -> SET : 1025, TAG : 129704656896
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42915313221632
L3 MISS -> SET : 0, TAG : 21457656610816
[LRU Victim] Cache miss in index : 0, 15
L2 HIT : 409, 4, 60
L2 MISS -> SET : 0, TAG : 4299171592
L3 MISS -> SET : 0, TAG : 2149585796
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3958400
L3 MISS -> SET : 4, TAG : 1979200
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275534053376
L3 MISS -> SET : 0, TAG : 137767026688
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259786801153
L3 MISS -> SET : 1025, TAG : 129893400576
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42932493090816
L3 MISS -> SET : 0, TAG : 21466246545408
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 499, TAG : 60
L3 HIT : 499, 5, 30
L2 MISS -> SET : 0, TAG : 4299171596
L3 MISS -> SET : 0, TAG : 2149585798
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 3964160
L3 MISS -> SET : 4, TAG : 1982080
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275533529088
L3 MISS -> SET : 0, TAG : 137766764544
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 259430285313
L3 MISS -> SET : 1025, TAG : 129715142656
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 42915313221632
L3 MISS -> SET : 0, TAG : 21457656610816
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 414, TAG : 60
L3 HIT : 414, 9, 30
L2 MISS -> SET : 0, TAG : 4299171596
L3 MISS -> SET : 0, TAG : 2149585798
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 12889096128
L3 MISS -> SET : 4, TAG : 6444548064
[LRU Victim] Cache miss in index : 4, 11
L2 MISS -> SET : 0, TAG : 275537461248
L3 MISS -> SET : 0, TAG : 137768730624
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 2511339777
L3 MISS -> SET : 1025, TAG : 1255669888
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 44117904064512
L3 MISS -> SET : 0, TAG : 22058952032256
[LRU Victim] Cache miss in index : 0, 15
L2 HIT : 597, 1, 0
L2 HIT : 0, 5, 0
L2 MISS -> SET : 1, TAG : 87745757441
L3 MISS -> SET : 1025, TAG : 43872878720
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41128606826496
L3 MISS -> SET : 0, TAG : 20564303413248
[LRU Victim] Cache miss in index : 0, 15
L2 HIT : 1007, 2, 6
L2 MISS -> SET : 0, TAG : 1103810798952
L3 MISS -> SET : 0, TAG : 551905399476
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 460621
L3 MISS -> SET : 1028, TAG : 230310
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275505479680
L3 MISS -> SET : 0, TAG : 137752739840
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 15361245441
L3 MISS -> SET : 1025, TAG : 7680622720
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41128606826496
L3 MISS -> SET : 0, TAG : 20564303413248
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 619, TAG : 3
L3 HIT : 1643, 12, 1
L2 MISS -> SET : 0, TAG : 1103810798952
L3 MISS -> SET : 0, TAG : 551905399476
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 246351
L3 MISS -> SET : 1028, TAG : 123175
[LRU Victim] Cache miss in index : 1028, 7
L2 MISS -> SET : 0, TAG : 275505479680
L3 MISS -> SET : 0, TAG : 137752739840
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 1, TAG : 16274096385
L3 MISS -> SET : 1025, TAG : 8137048192
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41128606826496
L3 MISS -> SET : 0, TAG : 20564303413248
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 267, TAG : 5
L3 HIT : 1291, 11, 2
L2 MISS -> SET : 0, TAG : 1103810798952
L3 MISS -> SET : 0, TAG : 551905399476
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 478927
L3 MISS -> SET : 1028, TAG : 239463
[LRU Victim] Cache miss in index : 1028, 7
L2 HIT : 0, 5, 0
L2 MISS -> SET : 1, TAG : 25872498945
L3 MISS -> SET : 1025, TAG : 12936249472
[LRU Victim] Cache miss in index : 1025, 14
L2 MISS -> SET : 0, TAG : 41128606826496
L3 MISS -> SET : 0, TAG : 20564303413248
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 48, TAG : 6
L3 HIT : 48, 14, 3
L2 MISS -> SET : 0, TAG : 1103810798952
L3 MISS -> SET : 0, TAG : 551905399476
[LRU Victim] Cache miss in index : 0, 15
L2 MISS -> SET : 4, TAG : 484381
```

 
### Disclaimer

Ignore the html and ./assets folder. 
It is not a part of the project.

Thanks.
