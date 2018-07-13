/*
  File:    main.c
  Created: 110718
*/

#include "fbe.h"
#include <stdio.h>

// main
int
main (int argc, char **argv)
{
 // basic sanity check
 if (argc < 2)
 {
   stats_file(NULL, FBE_DEFAULT_SEGMENT_SIZE);
 }
 else
 {
   stats_file(argv[1], FBE_DEFAULT_SEGMENT_SIZE);
 }

 return 0;
}

// ** EOF **
