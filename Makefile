LIB= -lfl

SRC= cool.l cool.y
CSRC= coolc-driver.cc cgen.cc cgen-supp.cc semant.cc utilities.cc \
	  stringtab.cc dumptype.cc tree.cc cool-tree.cc handle_flags.cc
CGEN= cool-lex.cc cool-parse.cc
HGEN= cool-parse.tab.h
CFIL= ${CSRC} ${CGEN}
OBJS= ${CFIL:.cc=.o}
OUTPUT= cool-parse.output

CPPINCLUDE= -I. -I./include

FFLAGS= -d -o cool-lex.cc
BFLAGS= --defines=cool-parse.tab.h -v -y --debug -p cool_yy -o cool-parse.cc

CC= g++
CFLAGS= -g -Wall -Wno-unused -Wno-write-strings -DDEBUG ${CPPINCLUDE}
FLEX= flex ${FFLAGS}
BISON= bison ${BFLAGS}
DEPEND= ${CC} -MM ${CPPINCLUDE}

all: coolc

%.d: %.cc ${SRC}
	${SHELL} -ec '${DEPEND} $< | sed '\''s/\($*\.o\)[ :]*/\1 $@ : /g'\'' > $@'

-include ${CFIL:.cc=.d}

coolc: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o $@

.cc.o:
	${CC} ${CFLAGS} -c $<

cool-lex.cc: cool.l
	${FLEX} cool.l

cool-parse.cc cool-parse.h: cool.y
	${BISON} cool.y

clean :
	-rm -f ${OUTPUT} *.s core ${OBJS} ${CGEN} ${HGEN} coolc *~ *.a *.o *.d

clean-compile:
	@-rm -f core ${OBJS} ${CGEN} ${HGEN}

