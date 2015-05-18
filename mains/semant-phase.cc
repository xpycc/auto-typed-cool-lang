#include <stdio.h>
#include <unistd.h>    // for getopt
#include "cool-tree.h"

extern Program ast_root;      // root of the abstract syntax tree
FILE *fin;        // we read the file from fin
extern int cool_yyparse(void); // entry point to the COOL parser
extern int optind;

extern int curr_lineno;
char *curr_filename;
extern int omerrs;             // a count of lex and parse errors

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
    ast_root->semant();
    ast_root->dump_with_types(cout,0);
  } else {
    fprintf(stderr, "%s: no input file.\n", argv[0]);
    exit(1);
  }
  return 0;
}

