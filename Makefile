#
# project, 2018 by Antonio Dell'elce, antonio@dellelce.com
#

CC             = gcc
TARGET         = target

SHELL          = /bin/bash

CFILES         = src/main.c src/print.c src/segments.c src/stats.c
OFILES         = obj/main.o obj/print.o obj/segments.o obj/stats.o
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

obj/main.o: src/main.c $(HFILES) includes/fbe.h
	@echo "CC "src/main.c
	@$(CC) -c $(CFLAGS) -o obj/main.o src/main.c

obj/print.o: src/print.c $(HFILES) includes/fbe.h
	@echo "CC "src/print.c
	@$(CC) -c $(CFLAGS) -o obj/print.o src/print.c

obj/segments.o: src/segments.c $(HFILES) includes/fbe.h
	@echo "CC "src/segments.c
	@$(CC) -c $(CFLAGS) -o obj/segments.o src/segments.c

obj/stats.o: src/stats.c $(HFILES) includes/fbe.h
	@echo "CC "src/stats.c
	@$(CC) -c $(CFLAGS) -o obj/stats.o src/stats.c


#
# clean
#

clean:
	rm -f $(TARGET) $(OFILES) $(LOC_HFILES) *.exe

#
# redo
#

redo: clean all

