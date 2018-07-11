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
 if (argc < 2) { printf("missing filename\n"); return 1; }

 // main code
 stats_file(argv[1], 1024);

 return 0;
}

// ** EOF **
