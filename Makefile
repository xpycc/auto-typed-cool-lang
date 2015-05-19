LIB= -lfl		# for yywrap()

SRC= cool.l cool.y
CSRC= utilities.cc  stringtab.cc dumptype.cc tree.cc cool-tree.cc handle_flags.cc
LSRC= lextest.cc semant.cc cgen.cc cgen-supp.cc
PSRC= parser-phase.cc semant.cc cgen.cc cgen-supp.cc
SSRC= semant-phase.cc semant.cc cgen.cc cgen-supp.cc
DSRC= coolc-driver.cc cgen.cc cgen-supp.cc semant.cc
LGEN= cool-lex.cc
PGEN= cool-lex.cc cool-parse.cc
HGEN= cool-parse.tab.h
LFIL= ${LSRC} ${CSRC} ${LGEN}
PFIL= ${PSRC} ${CSRC} ${PGEN}
SFIL= ${SSRC} ${CSRC} ${PGEN}
DFIL= ${DSRC} ${CSRC} ${PGEN}
LOBJ= ${LFIL:.cc=.o}
POBJ= ${PFIL:.cc=.o}
SOBJ= ${SFIL:.cc=.o}
DOBJ= ${DFIL:.cc=.o}
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

-include ${DFIL:.cc=.d}

lexer: ${LOBJ}
	${CC} ${CFLAGS} ${LOBJ} ${LIB} -o $@

parser: ${POBJ}
	${CC} ${CFLAGS} ${POBJ} ${LIB} -o $@

semant: ${SOBJ}
	${CC} ${CFLAGS} ${SOBJ} ${LIB} -o $@

coolc: ${DOBJ}
	${CC} ${CFLAGS} ${DOBJ} ${LIB} -o $@

.cc.o:
	${CC} ${CFLAGS} -c $<

cool-lex.cc: cool.l
	${FLEX} cool.l

cool-parse.cc: cool.y
	${BISON} cool.y

lextest.cc:
	ln -s mains/lextest.cc

parser-phase.cc:
	ln -s mains/parser-phase.cc

semant-phase.cc:
	ln -s mains/semant-phase.cc

clean :
	-rm -f ${OUTPUT} ${PGEN} ${HGEN} *.s core coolc *~ *.a *.o *.d
	-rm -f lextest.cc parser-phase.cc semant-phase.cc lexer parser semant

clean-compile:
	@-rm -f core *.o ${PGEN} ${HGEN}

