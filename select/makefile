#******************************************************************************
#* $Id: makefile,v 0.00 2015/10/16 22:50:55 gene Exp $
#******************************************************************************
#* Author: Gerd Neugebauer
#*=============================================================================

CFLAGS = -I ../include -DREGEX

OFILES  = ../crossref.o	\
	  ../database.o	\
	  ../entry.o	\
	  ../error.o	\
	  ../expand.o	\
	  ../init.o	\
	  ../key.o	\
	  ../macros.o	\
	  ../names.o	\
	  ../parse.o	\
	  ../print.o	\
	  ../pxfile.o	\
	  ../record.o	\
	  ../rewrite.o	\
	  ../rsc.o	\
	  ../s_parse.o	\
	  ../symbols.o	\
	  ../stack.o	\
	  ../sbuffer.o	\
	  ../tex_aux.o	\
	  ../tex_read.o	\
	  ../type.o	\
	  ../version.o	\
	  ../wordlist.o	\
	  ../regex.o

all: com_test

com_test: com_test.o term.o commands.o $(OFILES) eval_term.o
	$(CC) -g -O2 -o $@ com_test.o term.o commands.o $(OFILES) eval_term.o -lkpathsea 

commands.o: term.h commands.h

commands.c commands.h: commands.y
	$(YACC) -d $<
	mv y.tab.c commands.c
	mv y.tab.h commands.h

term.o: term.h commands.h

eval_term.o: term.h commands.h

clean:
	rm -f *.o

#
