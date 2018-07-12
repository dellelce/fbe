/*

   File:    segments.c
   Created: 110718

*/

#include "fbe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* create empty fbe_stats_t object */
fbe_stats_t *
fbe_stats_init(unsigned int nsegs)
{
 fbe_stats_t         *s;
 fbe_stats_segment_t *seg;

 if (nsegs == 0) nsegs = FBE_DEFAULT_SEGMENT_CNT;

 s = malloc(sizeof(fbe_stats_t));

 if (s == NULL) return NULL;

 // initial setup
 s->segment_array_size = nsegs;
 s->segment_array_used = 0;

 s->segments = (fbe_stats_segment_t  **) malloc(sizeof(fbe_stats_segment_t *) * nsegs);

 seg =  (fbe_stats_segment_t *) malloc(sizeof(fbe_stats_segment_t));
 s->segments[0] = seg;
 s->segments[1] = NULL;

 memset(seg, 0, sizeof(fbe_stats_segment_t));

 return s;
}

void
fbe_stats_free(fbe_stats_t *stats)
{
 int pos;
 fbe_stats_segment_t *seg;

 /* steps:

    1. free every segment in stats->segment
    2. free stats->segment (array of pointers)
    3. free main stats object

 */

 if (stats == NULL) return;
 if (stats->segments == NULL) return;

 while (pos >= 0)
 {
  seg = stats->segments[pos];

  if (seg != NULL) free(seg);
 }

 free (stats->segments);
}

/*
   add new segment
*/
fbe_stats_segment_t *
fbe_stats_new_segment(fbe_stats_t *stats)
{
 fbe_stats_segment_t *seg;

 if (/*slots available in stats->segments*/
     (stats->segment_array_size - stats->segment_array_used) != 0)
 {
   /*
       get index using stats->segment_array_used
       alloc new segment
       update entry in stats->segment
       increase stats->segment_array_used
   */
 }
 else
 {
   /*
      must:
         resize segment
      re-use one of new segments
   */
 }

 return seg;
}

/*
   fbe_stats_segment_print
*/
void
fbe_stats_segment_print(fbe_stats_segment_t *stats)
{
 unsigned int cnt = stats->total_bytes;
 unsigned short rc = 0;

 printf("Count = %d\n", cnt);
 printf("Total bits = %ld\n", stats->total_bits);
 printf("Avg bits = %lf\n", (double)stats->total_bits/(double)cnt);

 for (cnt = 0; cnt <= 255; cnt = cnt + 1)
 {
   printf(" ch %3d %6d", cnt, stats->charCount[cnt]);
   rc += 1;
   if (rc == 6) { printf("\n"); rc = 0; }
 }

 if (rc != 0) { printf("\n"); rc = 0; }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf(" zone %3d %6d", cnt, stats->zones[cnt]);
   rc += 1;
   if (rc == 6) { printf("\n"); rc = 0; }
 }

 if (rc != 0) { printf("\n"); rc = 0; }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf(" low  %3d %6d", cnt, stats->lowers[cnt]);
   rc += 1;
   if (rc == 6) { printf("\n"); rc = 0; }
 }
}

// ** EOF **
