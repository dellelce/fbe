/*

  Basic file statistics

  File:    stats.c
  Created: 040718

  TODO:
  * Currently all file is handled as a single unit
  * It should split in fixed blocks

*/
// includes

#include <stdio.h>
#include <math.h>

// functions

/*
   byte_weight

   this really should be done for a segment/block
*/

static unsigned short _nibble_weight[16] =
{
 0,  // 0000
 1,  // 0001
 1,  // 0010
 2,  // 0011
 1,  // 0100
 2,  // 0101
 2,  // 0110
 3,  // 0111
 1,  // 1000
 2,  // 1001
 2,  // 1010
 3,  // 1011
 2,  // 1100
 3,  // 1101
 3,  // 1110
 4   // 1111
};

unsigned short // returns 0-8
byte_weight(short byte)
{
 return _nibble_weight[(byte&0xF)] + _nibble_weight[(byte>>4)];
}

/*
   stats_file

   report some statistics abot a single file
*/
void
stats_file(char *name)
{
 unsigned int charCount[256] = { 0 };
 FILE *fp;
 int ch; // this must be signed as EOF is defined as -1 (TODO: check Posix spec)
 unsigned int cnt = 0;
 // keep track of upper 4 bits: TODO: check endianity issues at byte level
 // zone is defined as "upper nibble" (or first 4 bits)
 unsigned short zones[16];
 unsigned short zone = { 0 };

 // lowers
 unsigned short lowers[16];
 unsigned short lower = { 0 };

 // total bits
 unsigned long total_bits = 0;

 // averages - not needed now
 //unsigned short avg = 0;

 fp = fopen(name, "rb");

 if (fp == NULL) return;

 while ((ch = fgetc(fp)) != EOF)
 {
   //printf("%c\n", ch);
   cnt += 1;
   charCount[ch] = charCount[ch] + 1;

   zone = (ch >> 4);
   zones[zone] = zones[zone] + 1;

   lower = ch & 0x0F;
   lowers[lower] = lowers[lower] + 1;

   total_bits += byte_weight(ch);
 }

 printf("Count = %d\n", cnt);
 printf("Total bits = %ld\n", total_bits);
 printf("Avg bits = %lf\n", (double)total_bits/(double)cnt);

 for (cnt = 0; cnt <= 255; cnt = cnt + 1)
 {
   printf("ch %d %d\n", cnt, charCount[cnt]);
 }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf("zone %d %d\n", cnt, zones[cnt]);
 }

 for (cnt = 0; cnt < 16; cnt = cnt + 1)
 {
   printf("lower %d %d\n", cnt, lowers[cnt]);
 }

 fclose(fp);
}

// main

int
main (int argc, char **argv)
{
 // basic sanity check
 if (argv[1] == NULL || argv[1][0] == 0) { printf("missing filename\n"); return 1; }

 stats_file(argv[1]);

 return 0;
}

// ** EOF **
