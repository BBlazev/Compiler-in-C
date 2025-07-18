#include <stdio.h>
#include <stdbool.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef int8 Identifier;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char*)
#define $i (int)

#define dtype(e) _Generic((e), \
    int32: "int32", \
    char: "char", \
    int8*: "string", \
    int: "int", \
    char*: "string", \
    default: "" \
)

#define showtype(e) printf("%s :: (%s)\n", #e, dtype((e)))


typedef struct AST AST;

typedef struct AST {
  enum {
    AST_NUMBER,
    AST_VARIABLE,
    AST_ASSIGNMENT,
    AST_ADD,
    AST_MUL,
    AST_SUB,
    AST_DIV
  } tag;
  union {
    struct AST_NUMBER {int32 number; } AST_NUMBER;
    struct AST_ADD {AST *left; AST *right; } AST_ADD;
    struct AST_MUL {AST *left; AST *right; } AST_MUL;
    struct AST_SUB {AST *left; AST *right;} AST_SUB;
    struct AST_DIV {AST *left; AST *right;} AST_DIV;
    struct AST_VARIABLE {Identifier* name;} AST_VARIABLE;
    struct AST_ASSIGNMENT {Identifier* variable_name; AST *expression;} AST_ASSIGNMENT;
  } data;
} AST;





typedef enum TokenType {
    TOKEN_EOF,          // End of input
    TOKEN_IDENTIFIER,   // Variable names, function names
    TOKEN_NUMBER,       // Integer literals
    TOKEN_STRING,       // String literals "..."
    TOKEN_KEYWORD,      // let, if, else, while, etc.
    
    // Operators
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_MULTIPLY,     // *
    TOKEN_DIVIDE,       // /
    TOKEN_ASSIGN,       // =
    TOKEN_EQUAL,        // ==
    TOKEN_NOT_EQUAL,    // !=
    TOKEN_LESS,         // <
    TOKEN_GREATER,      // >
    TOKEN_LESS_EQUAL,   // <=
    TOKEN_GREATER_EQUAL,// >=
    
    // Delimiters
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_LBRACE,       // {
    TOKEN_RBRACE,       // }
    TOKEN_SEMICOLON,    // ;
    TOKEN_COMMA,        // ,
    
    TOKEN_ERROR         // Error token
} TokenType;

typedef struct Token {
    TokenType type;
    int8* value;        // The actual text
    int16 length;       // Length of the token
    int16 line;         // Line number (for error reporting)
    int16 column;       // Column number
} Token;

// Lexer state
typedef struct Lexer {
    int8* input;        // The input string
    int8* current;      // Current position in input
    int16 line;         // Current line number
    int16 column;       // Current column number
} Lexer;

typedef struct Keyword {
    int8* word;
    int16 length;
} Keyword;




void copy(int8*, int8*, int16);
void zero(int8*, int16);
int8* readline(void);
int16 length(int8*);


AST* create_number_node(int32 num);
AST* create_variable_node(Identifier* s);
AST* create_binary_operation(AST* left, int operator_type, AST* right);
AST* create_assignment_node(Identifier* variable_name, AST* expression);
void cleanup_AST(AST* p);


void init_lexer(Lexer* lexer, int8* input);
Token next_token(Lexer* lexer);
Token make_token(TokenType type, int8* start, int16 length, int16 line, int16 column);
void free_token(Token* token);
bool is_keyword(int8* text, int16 length);
void print_token(Token* token);