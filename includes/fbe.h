/*
   fbe.h

   Proper Description to come soon

   Guidelines in WIP mode
*/

#ifndef __FBE_H
#define __FBE_H 1

// statistics structures - WIP

typedef struct _fbe_stat_entry
{
 unsigned short  type;
 unsigned int    id;
 unsigned int    value;
} fbe_stat_entry_t;

// segment stats
typedef struct _fbe_stats_segment
{
 int             charCount[256];

 // keep track of upper 4 bits: TODO: check endianness issues at byte level
 // zone is defined as "upper nibble" (or first 4 bits)
 unsigned short  zones[16];
 unsigned short  zone;

 // lowers
 unsigned short  lowers[16];
 unsigned short  lower;

 // total bits
 unsigned long   total_bits;

 // total bytes
 unsigned long   total_bytes;

 // id
 unsigned int    id;
} fbe_stats_segment_t;

// each segment has its own statistics structure and "fbe_stats_t" keeps a pointer to it
typedef struct _fbe_stats
{
  int                    segment_array_size;
  int                    segment_array_used;
  fbe_stats_segment_t  **segments;
} fbe_stats_t;


// default segment size
#ifndef FBE_DEFAULT_SEGMENT_SIZE
#define FBE_DEFAULT_SEGMENT_SIZE    2048
#endif // FBE_DEFAULT_SEGMENT_SIZE

// default number of segmens (when creating fbe_stats_t)
#ifndef FBE_DEFAULT_SEGMENT_CNT
#define FBE_DEFAULT_SEGMENT_CNT    128
#endif // FBE_DEFAULT_SEGMENT_CNT


#ifndef FBE_PRINT_COLUMNS
#define FBE_PRINT_COLUMNS    6
#endif // FBE_PRINT_COLUMNS

// Prototypes
void stats_file(char *name, unsigned int segment_size);

fbe_stats_t *fbe_stats_init(unsigned int nsegs);
fbe_stats_segment_t *fbe_stats_new_segment(fbe_stats_t *stats);
void fbe_stats_free(fbe_stats_t *stats);
void fbe_stats_segment_print(fbe_stats_segment_t *stats);

#endif // __FBE_H
