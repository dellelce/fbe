/*
   stacks.h

   FBE stacks code
*/

#ifndef __STACKS_H
#define __STACKS_H 1


// stacks of int
// C needs templates (but it not needs C++)


/*
  Why use slices?

  So that changes (pushes, pops) only affect the top and bottom slice only
  The middle slice(s) are unaffected

  Stacks are of fixed size and when you push an item the oldest item in the stack is removed
  So a push is two actual (update both bottom and top slice)

  Removing the item from the bottom is the most expensive (as it may take  more steps...)
*/


typedef struct __stack_int
{
 /* body */

 void       *slice;
 unsigned int sliceNum;
 unsigned int sliceSize;

} stack_int_t;


#endif // __STACKS_H
