/*
   File:    segments.c
   Created: 110718
*/

#include "fbe.h"

#include <stdlib.h>
#include <string.h>

/*
   fbe_stats_init

   create empty fbe_stats_t object
*/
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

 s->segments[0] = NULL;
 s->segments[1] = NULL;

 memset(seg, 0, sizeof(fbe_stats_segment_t));

 return s;
}

/*
  fbe_stats_free

  free all stats objects
*/
void
fbe_stats_free(fbe_stats_t *stats)
{
 int pos = stats->segment_array_used;
 fbe_stats_segment_t *seg;

 /* sanity */
 if (stats == NULL) return;
 if (stats->segments == NULL) return;

 while (pos >= 0)
 {
  seg = stats->segments[pos];

  if (seg != NULL) free(seg);
  pos -= 1;
 }

 free (stats->segments);
 free (stats);
}

/*
   add new segment
*/
fbe_stats_segment_t *
fbe_stats_new_segment(fbe_stats_t *stats)
{
 fbe_stats_segment_t *seg;

 seg = (fbe_stats_segment_t *) malloc (sizeof(fbe_stats_segment_t));
 if (seg == NULL) return NULL;

 memset(seg, 0, sizeof(fbe_stats_segment_t));

 // add new seg
 if (/*are slots available in stats->segments*/
     (stats->segment_array_size - stats->segment_array_used) != 0)
 {
   stats->segments[stats->segment_array_used] = seg;
   stats->segment_array_used += 1;
 }
 else
 {
   /* segments exhausted * TODO: need to do more checks on new array */
   int newcnt = stats->segment_array_size * 2;
   fbe_stats_segment_t  **_segs;

   _segs = realloc(stats->segments, sizeof(fbe_stats_segment_t *) * newcnt);
   if (_segs == NULL) { free(seg); return NULL; } // will this ever happen?

   stats->segments = _segs;
   stats->segment_array_size = newcnt;
   stats->segment_array_used += 1;
 }

 return seg;
}

// ** EOF **
