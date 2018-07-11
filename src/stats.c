/*

  Basic file statistics

  File:    stats.c
  Created: 040718

  TODO:
  * Currently all file is handled as a single unit
  * It should split in fixed blocks

*/


#include <stdio.h>
#include <math.h>

#include "fbe.h"

// functions

/*
   byte_weight

   this really should be done for a segment/block
*/

static unsigned short _nibble_weight[16] =
{
 0,  // 0000
 1,  // 0001
 1,  // 0010
 2,  // 0011
 1,  // 0100
 2,  // 0101
 2,  // 0110
 3,  // 0111
 1,  // 1000
 2,  // 1001
 2,  // 1010
 3,  // 1011
 2,  // 1100
 3,  // 1101
 3,  // 1110
 4   // 1111
};

unsigned short // returns 0-8
byte_weight(short byte)
{
 return _nibble_weight[(byte&0xF)] + _nibble_weight[(byte>>4)];
}

/*
   stats_file

   report some statistics abot a single file
*/
void
stats_file(char *name, unsigned int segment_size)
{
 FILE *fp;
 int ch; // this must be signed as EOF is defined as -1
 unsigned int cnt = 0;

 //
 fbe_stats_summary_t  summary = { 0 };

 fp = fopen(name, "rb");

 if (fp == NULL) return;

 while ((ch = fgetc(fp)) != EOF)
 {
   cnt += 1;
   summary.charCount[ch] = summary.charCount[ch] + 1;

   summary.zone = (ch >> 4);
   summary.zones[summary.zone] = summary.zones[summary.zone] + 1;

   summary.lower = ch & 0x0F;
   summary.lowers[summary.lower] = summary.lowers[summary.lower] + 1;

   summary.total_bits += byte_weight(ch);
 }

 printf("Count = %d\n", cnt);
 printf("Total bits = %ld\n", summary.total_bits);
 printf("Avg bits = %lf\n", (double)summary.total_bits/(double)cnt);

 for (cnt = 0; cnt <= 255; cnt = cnt + 1)
 {
   printf("ch %d %d\n", cnt, summary.charCount[cnt]);
 }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf("zone %d %d\n", cnt, summary.zones[cnt]);
 }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf("lower %d %d\n", cnt, summary.lowers[cnt]);
 }

 fclose(fp);
}


// main
int
main (int argc, char **argv)
{
 // basic sanity check
 if (argc < 2) { printf("missing filename\n"); return 1; }

 // main code
 stats_file(argv[1], 1024);

 return 0;
}

// ** EOF **
