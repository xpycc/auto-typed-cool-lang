//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include <iostream>
#include "tree.h"
#include "cool.h"
#include "stringtab.h"
#define yylineno curr_lineno;
extern int yylineno;

inline Boolean copy_Boolean(Boolean b) {return b; }
inline void assert_Boolean(Boolean) {}
inline void dump_Boolean(ostream& stream, int padding, Boolean b)
	{ stream << pad(padding) << (int) b << "\n"; }

void dump_Symbol(ostream& stream, int padding, Symbol b);
void assert_Symbol(Symbol b);
Symbol copy_Symbol(Symbol b);

class Program_class;
typedef Program_class *Program;
class Class__class;
typedef Class__class *Class_;
class Feature_class;
typedef Feature_class *Feature;
class Formal_class;
typedef Formal_class *Formal;
class Expression_class;
typedef Expression_class *Expression;
class Case_class;
typedef Case_class *Case;

typedef list_node<Class_> Classes_class;
typedef Classes_class *Classes;
typedef list_node<Feature> Features_class;
typedef Features_class *Features;
typedef list_node<Formal> Formals_class;
typedef Formals_class *Formals;
typedef list_node<Expression> Expressions_class;
typedef Expressions_class *Expressions;
typedef list_node<Case> Cases_class;
typedef Cases_class *Cases;

#define Program_EXTRAS                              \
virtual void semant() = 0;                          \
virtual void cgen(ostream&) = 0;                    \
virtual void dump_with_types(ostream&, int) = 0; 

#define program_EXTRAS                              \
void cgen(ostream&);                                \
void semant();     		                              \
void dump_with_types(ostream&, int);            

#define Class__EXTRAS                               \
virtual Symbol get_name() const = 0;                \
virtual Symbol get_parent() const = 0;              \
virtual Features get_features() const = 0;          \
virtual Symbol get_filename() const = 0;            \
virtual void dump_with_types(ostream&,int) = 0;


#define class__EXTRAS                               \
Symbol get_name() const { return name; }            \
Symbol get_parent() const { return parent; }        \
Features get_features() const { return features; }  \
Symbol get_filename() const { return filename; }    \
void dump_with_types(ostream&,int);   


#define Feature_EXTRAS                              \
virtual void dump_with_types(ostream&,int) = 0;     \
virtual Symbol get_name() const = 0;


#define Feature_SHARED_EXTRAS                       \
void dump_with_types(ostream&,int);                 \

#define method_EXTRAS                               \
Symbol get_name() const { return name; }            \
Formals get_formals() const { return formals; }     \
Symbol get_return_type() const { return return_type; }  \
Expression get_expr() const { return expr; }

#define attr_EXTRAS                                 \
Symbol get_name() const { return name; }            \
Symbol get_type_decl() const { return type_decl; }  \
Expression get_init() const { return init; }

#define Formal_EXTRAS                               \
virtual void dump_with_types(ostream&,int) = 0;     \
virtual Symbol get_name() const = 0;                \
virtual Symbol get_type_decl() const = 0;

#define formal_EXTRAS                               \
void dump_with_types(ostream&,int);                 \
Symbol get_name() const { return name; }            \
Symbol get_type_decl() const { return type_decl; }

#define Case_EXTRAS                                 \
virtual void dump_with_types(ostream& ,int) = 0;    \
virtual Symbol get_name() const = 0;                \
virtual Symbol get_type_decl() const = 0;           \
virtual Expression get_expr() const = 0;

#define branch_EXTRAS                               \
void dump_with_types(ostream& ,int);                \
Symbol get_name() const { return name; }            \
Symbol get_type_decl() const { return type_decl; }  \
Expression get_expr() const { return expr; }

#define Expression_EXTRAS                           \
Symbol type;                                        \
Symbol get_type() { return type; }                  \
Expression set_type(Symbol s) { type = s; return this; }  \
virtual void dump_with_types(ostream&,int) = 0;     \
virtual void code(ostream&) = 0;                    \
void dump_type(ostream&, int);                      \
Expression_class() { type = (Symbol) NULL; }        \
virtual Symbol check_type() = 0;

#define Expression_SHARED_EXTRAS                    \
void code(ostream&);                                \
void dump_with_types(ostream&,int);                 \
Symbol check_type();


#endif
