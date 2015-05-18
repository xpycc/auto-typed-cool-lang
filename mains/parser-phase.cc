//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

//////////////////////////////////////////////////////////////////////////////
//
//  parser-phase.cc
//
//  Reads a COOL token stream from a file and builds the abstract syntax tree.
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>     // for Linux system
#include <unistd.h>    // for getopt
#include "cool-io.h"  //includes iostream
#include "cool-tree.h"
#include "utilities.h"  // for fatal_error
#include "cool-parse.h"

//
// These globals keep everything working.
//
FILE *fin;		// we read from this file
extern int optind;
extern Classes parse_results;	 // list of classes; used for multiple files 
extern Program ast_root;	 // the AST produced by the parse

extern int curr_lineno;    // defined in tree.cc
char *curr_filename;

extern int omerrs;             // a count of lex and parse errors

extern int cool_yyparse();
void handle_flags(int argc, char *argv[]);

int argcc; char **argvv;

int main(int argc, char *argv[]) {
  handle_flags(argc, argv);
  argcc = argc; argvv = argv;
  if (optind < argc) {
    if ((fin = fopen(argv[optind], "r")) == NULL) {
      cerr << "Could not open input file " << argv[optind] << endl;
      exit(1);
    }
    curr_lineno = 1;
    curr_filename = argv[optind++];
    cool_yyparse();
    if (omerrs != 0) {
      cerr << "Compilation halted due to lex and parse errors\n";
      exit(1);
    }
    ast_root->dump_with_types(cout,0);
  } else {
    fprintf(stderr, "%s: no input file.\n", argv[0]);
    exit(1);
  }
  return 0;
}

