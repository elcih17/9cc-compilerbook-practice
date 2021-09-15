#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token
typedef enum {
  TK_RESERVED, // symbol
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
  ND_NUM, // integer
} NodeKind;

typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
};

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
Token *tokenize(char *p);
Node *new_node(NodeKind kind);
Node *new_node_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);

Node *expr();
// = equality
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
// = num | "(" expr ")"
