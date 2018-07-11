/*

   File:    segments.c
   Created: 110718

*/

#include "fbe.h"

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
  /* steps:

     1. free every segment in stats->segment
     2. free stats->segment (array of pointers)
     3. free main stats object

  */
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
   */
 }

 return seg;
}


// ** EOF **
