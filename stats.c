/* 

  Basic file statistics

  File:    stats.c
  Created: 040718

*/

// includes

#include <stdio.h>

// main

int
main (int argc, char **argv)
{
 unsigned int charCount[256] = { 0 };
 FILE *fp;
 int ch; // this must be signed as EOF is defined as -1 (TODO: check Posix spec)
 unsigned int cnt = 0;
 // keep track of upper 4 bits: TODO: checked endianity issues at byte level
 // zone is defined as "upper nibble" (or first 4 bits)
 unsigned short zones[16];
 unsigned short zone = { 0 };

 // lowers
 unsigned short lowers[16];
 unsigned short lower = { 0 };

 // basic sanity check
 if (argv[1] == NULL || argv[1][0] == 0) { printf("missing filename\n"); return 1; }
 
 fp = fopen(argv[1], "rb");

 while ((ch = fgetc(fp)) != EOF)
 {
   //printf("%c\n", ch);
   cnt += 1;
   charCount[ch] = charCount[ch] + 1;

   zone = (ch >> 4);
   zones[zone] = zones[zone] + 1;

   lower = ch & 0x0F;
   lowers[lower] = lowers[lower] + 1;
 }

 printf("Count = %d\n", cnt);

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

 fflush(stdout);
 fclose(fp);
 // generic return

 return 0;
}

// ** EOF **
