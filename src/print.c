/*
   File:    print.c
   Created: 060818
*/

#include "fbe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   fbe_stats_segment_print

   print a nice-ish report on a segment
*/
void
fbe_stats_segment_print(fbe_stats_segment_t *stats)
{
 unsigned int cnt = stats->total_bytes;
 unsigned short rc = 0;

 /* segment summary counters */
 printf("Count = %6d Total deltas = %6ld Total bits = %6lu Avg bits = %lf\n",
        cnt,
        stats->total_deltas,
        stats->total_bits,
        (double)stats->total_bits/(double)cnt
       );

 for (cnt = 0; cnt <= 255; cnt = cnt + 1)
 {
   printf(" ch %3d %6d", cnt, stats->charCount[cnt]);
   rc += 1;
   if (rc == FBE_PRINT_COLUMNS) { printf("\n"); rc = 0; }
 }

 if (rc != 0) { printf("\n"); rc = 0; }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf(" zone %3d %6d", cnt, stats->zones[cnt]);
   rc += 1;
   if (rc == FBE_PRINT_COLUMNS) { printf("\n"); rc = 0; }
 }

 if (rc != 0) { printf("\n"); rc = 0; }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf(" low  %3d %6d", cnt, stats->lowers[cnt]);
   rc += 1;
   if (rc == FBE_PRINT_COLUMNS) { printf("\n"); rc = 0; }
 }

 if (rc>0) printf("\n");
}

// ** EOF **
