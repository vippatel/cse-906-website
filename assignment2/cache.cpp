#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

typedef struct {
   unsigned long long tag;
   unsigned long long lru;
} cacheTag;

#define INVALID_TAG 0xfffffffffffffffULL
#define L1_NUMSET 2048
#define LOG_L1_NUMSET 11
#define L1_ASSOC 16
#define L1_BLOCK_SIZE 64
#define LOG_L1_BLOCK_SIZE 6

int main (int argc, char **argv)
{
   
   int i, j, k, m, L1setid, INVsetid, maxindex, numtraces, threadid;
   unsigned int x;
   unsigned long long addr, miss=0, max, l1_miss=0, l1_hit=0;
   char dest_file_name[256], dest_file_name_1[256], input_name[256];

   FILE *fp;
   FILE *fp1;
   FILE *fp2;
   cacheTag **cache;
   unsigned pc;
   int l1way, updateway;

   sprintf(dest_file_name, "%s-miss-trace", argv[1]);
   fp = fopen(dest_file_name, "w");
   assert(fp != NULL);

   //Definition of the single-level cache

   cache = (cacheTag**)malloc(L1_NUMSET*sizeof(cacheTag*));
   assert(cache != NULL);
   for (i=0; i<L1_NUMSET; i++) {
      cache[i] = (cacheTag*)malloc(L1_ASSOC*sizeof(cacheTag));
      assert(cache[i] != NULL);
      for (j=0; j<L1_ASSOC; j++) {
         cache[i][j].tag = INVALID_TAG;
      }
   }

    sprintf(input_name, "%s", argv[2]);
        std::cout << input_name[1];

      fp1 = fopen(input_name, "r");
      assert(fp1 != NULL);

      while (!feof(fp1)) {
         fread(&threadid, sizeof(int), 1, fp1);
         fread(&addr, sizeof(unsigned long long int), 1, fp1);
         fread(&x, sizeof(unsigned int), 1, fp1);
         

         L1setid = (addr >> LOG_L1_BLOCK_SIZE) & (L1_NUMSET - 1);
         
         // L1 cache lookup
         for (l1way=0; l1way<L1_ASSOC; l1way++) {
            if (cache[L1setid][l1way].tag == (addr >> LOG_L1_BLOCK_SIZE)) {
               l1_hit++;
               break;
            }
         }
         if (l1way==L1_ASSOC) {  // L1 cache miss
            l1_miss++;
            fprintf(fp, "%llu\n", addr);
                  
            // Now fill in L1 cache
            for (l1way=0; l1way<L1_ASSOC; l1way++) {
               if (cache[L1setid][l1way].tag == INVALID_TAG) break;
            }
            if (l1way==L1_ASSOC) {
               // Find LRU
               max = 0;
               for (l1way=0; l1way<L1_ASSOC; l1way++) {
                  if (cache[L1setid][l1way].lru >= max) {
                     max = cache[L1setid][l1way].lru;
                     maxindex = l1way;
                  }
               }
               l1way = maxindex;
            }
            assert(l1way < L1_ASSOC);
            cache[L1setid][l1way].tag = (addr >> LOG_L1_BLOCK_SIZE);
         }
         assert(l1way < L1_ASSOC);
         for (j=0; j<L1_ASSOC; j++) {
            cache[L1setid][j].lru++;
         }
         cache[L1setid][l1way].lru = 0;
         
      }
      fclose(fp1);

   sprintf(dest_file_name_1, "%s-hits-misses", argv[1]);
   fp2 = fopen(dest_file_name_1, "w");
   assert(fp2 != NULL);
   fprintf(fp2, "L1 Hits: %llu, L1 Misses: %llu\n", l1_hit, l1_miss);
   fclose(fp2);
   fclose(fp);
   return 0;
}
