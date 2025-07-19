# C Interpreter Project
![Intepreter](https://github.com/user-attachments/assets/13b6113b-a7e7-4afa-82b8-a2873656aff1)

A lightweight interpreter implementation written in C, featuring a complete parsing pipeline and dynamic variable management.

## Overview

This project implements a working programming language interpreter with:
- **Complete Lexer/Tokenizer** - Breaks source code into tokens (identifiers, operators, numbers, etc.)
- **Recursive Descent Parser** - Parses tokens into Abstract Syntax Trees (AST)
- **Symbol Table** - Dynamic variable storage with lookup and type safety
- **AST Evaluator** - Executes parsed code and manages program state
- **Interactive REPL** - Read-Eval-Print Loop with error handling
- **Memory Management** - Safe allocation/deallocation with custom utilities

## Features

### Current Implementation ✅
- **Variable Assignment**: Create variables with `x = 5` syntax
- **Variable Lookup**: Reference stored variables by name (`x`)
- **Symbol Table**: Array-based variable storage with collision detection
- **AST Generation**: Parse input into tree structures representing code
- **Type System**: Support for 32-bit integers with extensible type enum
- **Error Handling**: Graceful parsing error detection and reporting
- **Memory Safety**: Proper malloc/free patterns with cleanup functions

### Supported Operations
```bash
@> x = 5          # Create variable x with value 5
Assignment completed!

@> x              # Look up variable x  
Variable x = 5

@> y              # Try to access undefined variable
Variable not found

@> exit           # Quit interpreter
```

## Building

```bash
# Using the provided Makefile
make

# Or manually compile
gcc -O2 -Wall -std=c17 -c common.c
gcc -O2 -Wall -std=c17 -c intepreter.c parser.c
gcc -O2 -Wall -std=c17 common.o intepreter.o parser.o -o intepreter
```

## Usage

```bash
./intepreter
```

The interpreter starts with a prompt (`@> `) where you can:
- **Assign variables**: `variableName = number`
- **Look up variables**: `variableName`  
- **Exit**: Type `exit`

## Code Structure

```
├── common.h/c          # Lexer, AST definitions, utility functions
├── intepreter.h/c      # Variable system, symbol table, main loop
├── parser.h/c          # Recursive descent parser and evaluator
├── MakeFile           # Build configuration
└── README.md        
```

### Architecture

**Interpreter Pipeline:**
```
Source Code → Lexer → Parser → AST → Evaluator → Result
     "x=5"  →  [TOK] →  [AST] → [AST] →   x=5    → "Assignment completed!"
```

**Key Components:**
- **Lexer**: Tokenizes input using finite state machine
- **Parser**: Builds AST using recursive descent with proper error handling  
- **Symbol Table**: Manages variable lifetime and lookup (O(n) array-based)
- **Evaluator**: Executes AST nodes and updates program state
- **AST Nodes**: Support assignment, variable reference, and number literals

## TODO List

### Core Language Features
- [✅] **Lexical Analysis**
  - [✅] Implement tokenizer for keywords, operators, literals
  - [ ] Add support for comments (single-line `//` and multi-line `/* */`)
  - [✅] Handle whitespace and newlines properly

- [🔄] **Parser Implementation**
  - [✅] Build recursive descent parser
  - [✅] Support variable declarations (`x = 5`)
  - [ ] Parse expressions with operator precedence (`2 + 3 * 4`)
  - [ ] Add support for function definitions

- [ ] **Expression Evaluation**
  - [ ] Arithmetic operations (`+`, `-`, `*`, `/`, `%`)
  - [ ] Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)
  - [ ] Logical operators (`&&`, `||`, `!`)
  - [ ] String concatenation and comparison

### Variable System Enhancements
- [🔄] **Symbol Table**
  - [✅] Variable lookup and resolution
  - [ ] Scope management (global, local, block scope)

- [🔄] **Type System**
  - [✅] Integer type support
  - [ ] Boolean type with `true`/`false` literals
  - [ ] Type checking and conversion

### Control Flow
- [ ] **Conditional Statements**
  - [ ] `if`/`else` statements

- [ ] **Loops**
  - [ ] `while` loops
  - [ ] `break` and `continue` statements

### Functions and Procedures
- [ ] **Function System**
  - [ ] Function definition syntax
  - [ ] Parameter passing (by value/reference)
  - [ ] Return statements and values
  - [ ] Recursive function calls
  - [ ] Built-in functions (print, input, etc.)

### Advanced Features
- [🔄] **Error Handling**
  - [✅] Basic parsing error detection
  - [ ] Comprehensive error reporting with line numbers
  - [ ] Runtime error recovery

### REPL Improvements
- [🔄] **Enhanced Interface**
  - [✅] Basic command processing
  - [ ] Command history (up/down arrows)

- [ ] **REPL Commands**
  - [ ] `:help` - Show available commands
  - [ ] `:vars` - List all variables  
  - [ ] `:clear` - Clear all variables

**Legend:** ✅ Complete | 🔄 Partially Complete | [ ] Not Started
