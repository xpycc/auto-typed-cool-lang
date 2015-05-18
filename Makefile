LIB= -lfl

SRC= cool.l cool.y
CSRC= parser-phase.cc utilities.cc stringtab.cc dumptype.cc \
      tree.cc cool-tree.cc handle_flags.cc 
TSRC= mycoolc
HSRC= 
CGEN= cool-lex.cc cool-parser.cc
HGEN= cool-parser.hh
LIBS=
CFIL= ${CSRC} ${CGEN}
OBJS= ${CFIL:.cc=.o}
OUTPUT= good.output bad.output cool-parser.output

CPPINCLUDE= -I. -I./include

FFLAGS= -d -o cool-lex.cc
BFLAGS= -d -v -y --debug -p cool_yy -o cool-parser.cc

CC= g++
CFLAGS= -g -Wall -Wno-unused -Wno-write-strings -DDEBUG ${CPPINCLUDE}
FLEX= flex ${FFLAGS}
BISON= bison ${BFLAGS}
DEPEND= ${CC} -MM ${CPPINCLUDE}

%.d: %.cc ${SRC}
	${SHELL} -ec '${DEPEND} $< | sed '\''s/\($*\.o\)[ :]*/\1 $@ : /g'\'' > $@'

-include ${CFIL:.cc=.d}

parser: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o parser

.cc.o:
	${CC} ${CFLAGS} -c $<

cool-lex.cc: cool.l
	${FLEX} cool.l

cool-parser.cc cool-parser.h: cool.y
	${BISON} cool.y

dotest:	parser tests/parser-good.cl bad.cl tests/parser-bad.cl
	@echo "\nRunning parser on good.cl\n"
	-./parser tests/parser-good.cl
	@echo "\nRunning parser on bad.cl\n"
	-./parser tests/parser-bad.cl

clean :
	-rm -f ${OUTPUT} *.s core ${OBJS} ${CGEN} ${HGEN} lexer parser cgen semant *~ *.a *.o *.d

clean-compile:
	@-rm -f core ${OBJS} ${CGEN} ${HGEN}

