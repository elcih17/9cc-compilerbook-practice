#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token
typedef enum {
  TK_RESERVED, // symbol
  TK_IDENT,      // Identifier
  TK_NUM,      // integer
  TK_EOF,      // end of input
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind; // token kind
  Token *next;    // next token
  int val;        // if kind is TK_NUM, value of the token
  char *str;      // token string
  int len;        // token length
};

// Node
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LTE, // <=
  ND_ASSIGN, // =
  ND_LVAR, // local variable
  ND_NUM, // integer
} NodeKind;

typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val; // ND_NUM
  int offset; // ND_LVAR
};


//
// local variable
//
typedef struct LVar LVar;
struct LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
};
LVar *locals;
LVar *find_lvar(Token *tok);

//
// global
//

// current token
Token *token;

char *user_input;


//
// codegen
//
void codegen(Node *node);

//
// parse
//

// reports an error location and exit
void error_at(char *loc, char *fmt, ...);

bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();

Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startsWith(char *p, char *q);
Token *tokenize();
Node *new_node(NodeKind kind);
Node *new_node_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);

Node *code[100];
void program();
Node *stmt();
// = expr ";"
Node *expr();
// = assign
Node *assign();
// = equality ("=" assign)?
Node *equality();
// =  ("==" relational | "!=" relational)*
Node *relational();
// = add ("<" add | "<=" add | ">" add | ">=" add)*
Node *add();
// = mul ("+" mul | "-" mul)*
Node *mul();
// = unary ("*" unary | "/" unary)*
Node *unary();
// = ("+" | "-")? primary
Node *primary();
// = num | ident | "(" expr ")"
