# C Interpreter Project

A lightweight interpreter implementation written in C, featuring a custom type system and dynamic variable management.

## Overview

This project implements the foundation of a programming language interpreter with:
- Custom type definitions and casting macros
- Dynamic variable creation and management  
- Memory-safe string and numeric operations
- Interactive REPL (Read-Eval-Print Loop)
- Extensible architecture for language features

## Features

### Current Implementation
- **Variable Management**: Dynamic creation of variables with type safety
- **Memory Management**: Custom `zero()`, `copy()`, and `length()` functions for safe memory operations
- **Interactive Shell**: Basic REPL with command input and exit functionality
- **Type Detection**: Generic macro for runtime type identification

### Variable Types Supported
- `String`: Dynamic string storage with automatic memory management
- `Int`: 32-bit integer values  
- `Char`: Single character values
- Extensible enum for additional types

## Building

```bash
# Using the provided Makefile
make

# Or manually compile
gcc -O2 -Wall -std=c17 -c common.c
gcc -O2 -Wall -std=c17 -c intepreter.c  
gcc -O2 -Wall -std=c17 common.o intepreter.o -o intepreter
```

## Usage

```bash
./intepreter
```

The interpreter starts with a simple prompt (`@> `) where you can:
- Type `exit` to quit
- Enter other commands (currently just echoes back)

## Code Structure

```
├── common.h/c          # Core types, macros, and utilities
├── intepreter.h/c      # Main interpreter logic and Variable system
├── MakeFile           # Build configuration
└── README.md          # This file
```

### Key Components

- **Variable Structure**: Stores type, identifier, and value pointer
- **Creation Macros**: `newstr()`, `newint()`, `newchar()` for type-safe variable creation
- **Memory Utilities**: Safe string operations and memory management
- **REPL Loop**: Interactive command processing

## TODO List - at least some of it, hopefully

### Core Language Features
- [ ] **Lexical Analysis**
  - [✅] Implement tokenizer for keywords, operators, literals
  - [ ] Add support for comments (single-line `//` and multi-line `/* */`)
  - [✅] Handle whitespace and newlines properly

- [ ] **Parser Implementation**
  - [ ] Build recursive descent parser
  - [ ] Support variable declarations (`let x = 5`)
  - [ ] Parse expressions with operator precedence
  - [ ] Add support for function definitions

- [ ] **Expression Evaluation**
  - [ ] Arithmetic operations (`+`, `-`, `*`, `/`, `%`)
  - [ ] Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)
  - [ ] Logical operators (`&&`, `||`, `!`)
  - [ ] String concatenation and comparison

### Variable System Enhancements
- [ ] **Symbol Table**
  - [ ] Implement hash table for variable storage
  - [ ] Add scope management (global, local, block scope)
  - [ ] Variable lookup and resolution

- [ ] **Type System**
  - [ ] Add floating-point numbers (`float`, `double`)
  - [ ] Boolean type with `true`/`false` literals
  - [ ] Arrays/lists with indexing
  - [ ] Type checking and conversion

### Control Flow
- [ ] **Conditional Statements**
  - [ ] `if`/`else` statements
  - [ ] `switch`/`case` statements
  - [ ] Ternary operator (`?:`)

- [ ] **Loops**
  - [ ] `while` loops
  - [ ] `for` loops  
  - [ ] `do-while` loops
  - [ ] `break` and `continue` statements

### Functions and Procedures
- [ ] **Function System**
  - [ ] Function definition syntax
  - [ ] Parameter passing (by value/reference)
  - [ ] Return statements and values
  - [ ] Recursive function calls
  - [ ] Built-in functions (print, input, etc.)

### Advanced Features
- [ ] **Error Handling**
  - [ ] Comprehensive error reporting with line numbers
  - [ ] Runtime error recovery
  - [ ] Stack trace on errors

- [ ] **Memory Management**
  - [ ] Garbage collector implementation
  - [ ] Memory leak detection
  - [ ] Reference counting for complex types

- [ ] **Standard Library**
  - [ ] String manipulation functions
  - [ ] Math functions (`sqrt`, `pow`, `sin`, etc.)
  - [ ] File I/O operations
  - [ ] Array/list manipulation

### Developer Experience
- [ ] **Debugging Support**
  - [ ] Step-through debugger
  - [ ] Variable inspection
  - [ ] Breakpoints

- [ ] **Testing Framework**
  - [ ] Unit tests for core components
  - [ ] Integration tests for language features
  - [ ] Performance benchmarks

- [ ] **Documentation**
  - [ ] Language specification
  - [ ] API documentation
  - [ ] Tutorial and examples

### REPL Improvements
- [ ] **Enhanced Interface**
  - [ ] Command history (up/down arrows)
  - [ ] Tab completion for variables/functions
  - [ ] Syntax highlighting
  - [ ] Multi-line input support

- [ ] **REPL Commands**
  - [ ] `:help` - Show available commands
  - [ ] `:vars` - List all variables  
  - [ ] `:clear` - Clear all variables
  - [ ] `:load <file>` - Load and execute file
  - [ ] `:save <file>` - Save session to file

