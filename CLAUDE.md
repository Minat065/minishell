# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a minishell project, part of the 42 school curriculum. The project involves creating a basic shell implementation in C that can interpret and execute commands similar to bash.

## Current Project State

The project appears to be in its initial stages with:
- Project requirements documented in `en.subject.pdf` and `en.norm.pdf`
- Token structure definitions in `message (1).txt` containing lexer/parser structures
- No source code implementation yet

## Key Components to Implement

Based on the token structures found, the shell will need:
1. **Lexer/Tokenizer**: Convert input strings into tokens (already defined in `message (1).txt`)
2. **Parser**: Build command structures from tokens
3. **Executor**: Execute parsed commands
4. **Built-ins**: Implement shell built-in commands (cd, echo, env, export, unset, exit, pwd)
5. **Signal Handling**: Handle signals like Ctrl+C, Ctrl+D, Ctrl+\
6. **Environment Variables**: Manage and expand environment variables
7. **Redirections**: Handle input/output redirections (<, >, >>, <<)
8. **Pipes**: Implement pipe functionality between commands

## Development Guidelines

### File Structure (Recommended)
```
minishell/
├── Makefile
├── includes/
│   ├── minishell.h
│   └── tokens.h (from message (1).txt)
├── srcs/
│   ├── main.c
│   ├── lexer/
│   ├── parser/
│   ├── executor/
│   ├── builtins/
│   ├── signals/
│   └── utils/
└── tests/
```

### Build Commands
Since no Makefile exists yet, when created it should include:
```bash
make        # Build the minishell executable
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild everything
```

### 42 School Norm Compliance
The project must comply with the 42 school coding norm (see `en.norm.pdf`). Key points typically include:
- Functions must not exceed 25 lines
- Maximum 5 functions per file
- Maximum 4 parameters per function
- Specific naming conventions
- No global variables unless static

### Testing Approach
When implementing tests:
- Test basic command execution
- Test redirections and pipes
- Test built-in commands
- Test signal handling
- Test edge cases and error handling

## Important Notes

1. The token structures in `message (1).txt` define a comprehensive token system supporting shell features like control structures (if/then/else, loops), which may be beyond the basic minishell requirements. Check `en.subject.pdf` for exact requirements.

2. Memory management is critical - ensure all mallocs are freed and no leaks occur.

3. Error handling should match bash behavior where specified in the subject.