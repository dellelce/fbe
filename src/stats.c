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
 unsigned int isPrinted = 0; // we need this for the "last" segment
 fbe_stats_t          *stats;
 fbe_stats_segment_t  *summary;

 stats = fbe_stats_init(0); // 0 = default
 summary = fbe_stats_new_segment(stats);

 if (name == NULL)
 {
  fp = stdin;
 }
 else
 {
  fp = fopen(name, "rb");
 }

 if (fp == NULL) return;

 while ((ch = fgetc(fp)) != EOF)
 {
   isPrinted = 0;
   cnt += 1;
   summary->charCount[ch] = summary->charCount[ch] + 1;

   summary->zone = (ch >> 4);
   summary->zones[summary->zone] = summary->zones[summary->zone] + 1;

   summary->lower = ch & 0x0F;
   summary->lowers[summary->lower] = summary->lowers[summary->lower] + 1;

   summary->total_bits += byte_weight(ch);

   if (cnt == segment_size)
   {
     summary->total_bytes = cnt;
     fbe_stats_segment_print(summary);
     cnt = 0;
     summary = fbe_stats_new_segment(stats);
     isPrinted = 1;
   }
 }

 if (isPrinted == 0)
 {
   printf("Last segment size = %d\n", cnt);
   summary->total_bytes = cnt;

   fbe_stats_segment_print(summary);
 }

 fbe_stats_free(stats); // summary is "cleaned" here as well

 fclose(fp);
}

// ** EOF **
