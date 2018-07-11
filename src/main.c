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
   stats_file(NULL, 1024);
 }
 else
 {
   stats_file(argv[1], 1024);
 }

 return 0;
}

// ** EOF **
