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

typedef struct _fbe_stats
{
 unsigned int        total;
 unsigned int        available;
 fbe_stat_entry_t   *entries;
} fbe_stats_t;

// summaries
typedef struct _fbe_stats_summary
{
 int            charCount[256];

 // keep track of upper 4 bits: TODO: check endianity issues at byte level
 // zone is defined as "upper nibble" (or first 4 bits)
 unsigned short zones[16];
 unsigned short zone;

 // lowers
 unsigned short lowers[16];
 unsigned short lower;

 // total bits
 unsigned long total_bits;
} fbe_stats_summary_t;


// Prototypes

void stats_file(char *name, unsigned int segment_size); // segment_size: unimplemented

#endif // __FBE_H
