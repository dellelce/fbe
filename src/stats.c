/*
  Compute statistics

  File:    stats.c
  Created: 040718

  TODO:
*/

#include <stdio.h>
#include <math.h>

#include "fbe.h"

// functions

/*
   byte_weight: count "ON" bits in a byte

   TODO: this really should be done for a segment/block
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
   bytes_distribution
*/
void
bytes_distribution(fbe_dist_reg_t *dist,
                   int             pos)
{
 if (dist->count == 0)
 {
   /* first entry in this distribution, do not calculate delta */
   dist->count = 1;
   dist->last  = pos;
 }
 else
 {
   dist->count += 1;
   dist->last_delta = pos - dist->last_delta;
   dist->last = pos;
 }
}

/*
   stats_file

   report some statistics abot a single file

   TODO: should be passed a buffer & pointer to fbe_stats_t
         and renamed to gather_stats() or something
*/
void
stats_file(char *name, unsigned int segment_size)
{
 unsigned int cnt = 0;
 unsigned int isPrinted = 0; // we need this for the "last" segment
 fbe_stats_t          *stats;
 fbe_stats_segment_t  *summary;
 // delta
 unsigned int previous = 0;
 int delta;
 FILE *fp;
 int ch; // this must be signed as EOF is defined as -1

 stats = fbe_stats_init(0); // 0 = default
 summary = fbe_stats_new_segment(stats);

 // read from stdin if no file provided
 if (name == NULL) { fp = stdin; } else { fp = fopen(name, "rb"); }

 if (fp == NULL) return;

 while ((ch = fgetc(fp)) != EOF)
 {
   isPrinted = 0;
   cnt += 1; // position processing segment
   summary->charCount[ch] = summary->charCount[ch] + 1;

   // keep counter for each zone (=top nibble)
   summary->zone = (ch >> 4);
   summary->zones[summary->zone] = summary->zones[summary->zone] + 1;

   // keep count for lower nibble
   summary->lower = ch & 0x0F;
   summary->lowers[summary->lower] = summary->lowers[summary->lower] + 1;

   // counter for total bits
   summary->total_bits += byte_weight(ch);

   // byte distribution
   bytes_distribution(&summary->dist[ch], summary->charCount[ch]);

   if (cnt > 1) /* are we after the first byte */
   {
    delta = previous - ch;

    if (delta != 0)
    {
     // decrease or increase by 1 if delta is not zero
     if (delta > 0) { summary->total_deltas += 1; } else { summary->total_deltas -= 1; }
    }
   }
   else { /* save previous */ previous = ch; }

   if (cnt == segment_size)
   {
     summary->total_bytes = cnt;
     fbe_stats_segment_print(summary);
     cnt = 0;
     summary = fbe_stats_new_segment(stats);
     isPrinted = 1;
   }
 } // end read loop

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
