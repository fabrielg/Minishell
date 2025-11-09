# Minishell

A compact, student-built shell in C that implements a real parsing → execution pipeline.  
This README explains how to build and run the project, what features are implemented, and how an input line is transformed step by step from user text to running processes.

---

## Build & run

Quick install

```bash
git clone https://github.com/fabrielg/Minishell && cd Minishell
```

Build:
```bash
make
```

Run:
```bash
./minishell
```
(That is all you need - the binary starts an interactive prompt.)

## 📂 Features

- **Builtins**: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- **External** command execution (via fork + execve)
- **Pipes**: `cmd1 | cmd2 | ... (N commands)`
- **Redirections**: input `<`, output `>`, append `>>`, heredoc `<<`
- **Subshells**: ( ... )
- **Logical operators**: `&&` and `||` with correct short-circuit behavior and precedence
- **Environment variable expansion** (`$VAR`, `$?`) performed at execution time
- **Quotes**: Proper handling of single and double quotes
- **Wildcards (globbing)** – support for `*` patterns for the current directory  
- **Signal handling** for interactive use (`Ctrl+C`, `Ctrl+D`, etc.)

## 💯 From input to execution - the full pipeline

When a user types a line, Minishell processes it through a sequence of well-defined stages:

- ### Readline
    The shell reads the raw input string from the user (interactive prompt, history, line editing).

- ### Lexing
    The lexer scans the raw string and produces base tokens: words, operators, parentheses, redirection symbols, quotes, etc.

- ### Parsing
    The parser analyses token sequences according to the grammar and groups tokens where appropriate (for example, associating redirections to a command). It also validates syntax (quotes, balanced parentheses, empty subshells () as errors, invalid operator sequences, ...).

- ### Token grouping / tokenization
    Tokens are organized into higher-level items representing commands and separators. This step produces a linear list of command tokens and operator tokens in the original order.

- ### AST building
    From that token list the AST (Abstract Syntax Tree) is built. The tree encodes operator precedence and grouping:

    - `&&` and `||` are logical nodes with left/right children and short-circuit semantics.

    - `|` (pipeline) nodes contain an ordered array of command nodes (not a binary left/right chain), simplifying multi-command pipelines.

- ### Subshell
    Subshell nodes hold their own AST for ( ... ).

- ### Redirections
    Redirections are attached to the command nodes they belong to.

- ### Execution
    The executor traverses the AST and runs commands:

    For a `COMMAND` node: expansions (environment variables, `$?`) are applied at execution time, then builtins or external commands run (builtins in parent process unless inside a pipeline).

    For a `PIPELINE` node: all commands in the pipeline are forked (N children), pipes are set up, unused FDs are closed in parent and children, and the parent waits for children. The pipeline exit status is the status of the last command.

    For `LOGICAL` nodes: execute left, inspect exit status, then decide to execute right based on `&&` `||`.

    For `SUBSHELL` nodes: the subshell AST is executed in a forked process with its own context.

## Example: token list → AST → execution
### Input
```bash
export TOTO=test && echo $TOTO | (cat -e | grep t)
```

### Lexer / token grouping (illustrative)
```bash
[T_CMD export] [T_WORD TOTO=test]
[T_LOGICAL &&]
[T_CMD echo] [T_WORD $TOTO]
[T_PIPE |]
[T_SUBSHELL (]
  [T_CMD cat] [T_WORD -e]
  [T_PIPE |]
  [T_CMD grep] [T_WORD t]
[T_SUBSHELL )]
```

### AST (conceptual)
```bash
LOGICAL (&&)
├─ COMMAND: export TOTO=test
└─ PIPELINE
   ├─ COMMAND: echo $TOTO
   └─ SUBSHELL:
      └─ PIPELINE
         ├─ COMMAND: cat -e
         └─ COMMAND: grep t
```

### Execution flow (what actually happens)

1. Execute `export TOTO=test` (in parent): sets `TOTO`.

2. Because export succeeded, evaluate the right side:

- Build pipeline for `echo $TOTO | (cat -e | grep t)`.

- `echo` is expanded at execution time → prints `test`.

- The pipeline forks `echo` and the subshell; data flows through pipes into the subshell.

- The subshell creates its own pipeline for `cat -e | grep t`, forks children, and runs them.

3. Exit statuses propagate: the pipeline status is that of its last command; logical operators use that to continue.

## A few behavioural notes

- **Expansions happen when a command is about to run**, not globally at parse time. This ensures constructs like `export X=1 && echo $X` behave as expected.

- **Pipelines fork all processes first** (no serial waits) so commands like `sleep 3 | sleep 3 | sleep 3` complete in ~3s, not 9s.

- **Pipes and file descriptors are carefully closed** in parent and children to ensure EOF is delivered and no commands hang waiting for input.

- **Empty subshell `()` is a syntax error** and reported as such.

- **Builtins inside pipelines** are executed in forked children to preserve parent state semantics.

## 👥 Team
- [@Fabrielg](https://github.com/fabrielg)
- [@Adeabreu711](https://github.com/Adeabreu711)