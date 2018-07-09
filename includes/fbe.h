/*
   fbe.h

   Proper Description to come soon

   Guidelines in WIP mode
*/

#ifndef __FBE_H
#define __FBE_H 1

// statistics structures

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
 fbe_stat_entry_ti  *entries;
} fbe_stats_t;


#endif // __FBE_H
