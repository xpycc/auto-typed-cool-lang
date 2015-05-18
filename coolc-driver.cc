#include <stdio.h>
#include <unistd.h>    // for getopt
#include "cool-tree.h"
#include "cgen_gc.h"

extern Program ast_root;      // root of the abstract syntax tree
FILE *fin;        // we read the file from fin
extern int cool_yyparse(void); // entry point to the COOL parser
extern int optind;

extern int curr_lineno;
char *curr_filename;
extern int omerrs;             // a count of lex and parse errors

void handle_flags(int argc, char *argv[]);
int argcc; char **argvv;

extern char *out_filename;     // code output file name

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
    if (!out_filename) {
      const int len = strlen(curr_filename);
      out_filename = new char[len + 8];
      strcpy(out_filename, curr_filename);
      char *dot = strrchr(out_filename, '.');
      if (!dot) dot = out_filename + len;
      strcpy(dot, ".s");
    }
    cool_yyparse();
    if (omerrs != 0) {
      cerr << "Compilation halted due to lex and parse errors\n";
      exit(1);
    }
    ast_root->semant();
    ofstream out(out_filename);
    if (!out) {
      fprintf(stderr, "%s: Cannot open output file %s\n", argv[0], out_filename);
      exit(1);
    }
    ast_root->cgen(out);
  } else {
    fprintf(stderr, "%s: no input file.\n", argv[0]);
    exit(1);
  }
  return 0;
}

