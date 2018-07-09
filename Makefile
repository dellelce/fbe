#
# project, 2018 by Antonio Dell'elce, antonio@dellelce.com
#

CC             = gcc
TARGET         = target

SHELL          = /bin/bash

CFILES         = src/stats.c
OFILES         = stats.o
LDFLAGS	       = 


LOC_HFILES     = 
HFILES         = $(LOC_HFILES)

INCLUDES       =  -I. -Iincludes
DEBUG          = 
CFLAGS         = -Wall -O2  $(INCLUDES) $(DEBUG)
LIBS           = 


#
# --- RULES ---
#

all: $(TARGET)

$(TARGET):   $(OFILES)
	@echo "LINK " $(TARGET)
	@$(CC) -o $(TARGET) $(LDFLAGS) $(OFILES) $(LIBS)

#
# -- DEPS --
#

stats.o: src/stats.c $(HFILES) includes/fbe.h
	@echo "CC "src/stats.c
	@$(CC) -c $(CFLAGS) -o stats.o src/stats.c

 
#  
# clean
#    
     
clean:
	rm -f $(TARGET) $(OFILES) $(LOC_HFILES) *.exe

#
# redo
#

redo: clean all

