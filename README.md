# Simple Line Editor

A terminal-based line editor written in C.

## Team Members

- Member 1: **Yeshwanth S**
- Member 2: **Ujwala**
- Member 3: **Shamathmica**

## Implemented Features

- Insert text at any valid line position.
- Delete lines by line number.
- Display the current document.
- Save the document to a text file and load it again later.
- Search for a word or phrase.
- Show line and word statistics.
- Built-in help command.

## Compile

Using GCC directly:

```text
gcc -std=c11 -Wall -Wextra -pedantic line_editor.c -o line_editor
```

On Windows, this creates `line_editor.exe` when using MinGW GCC. A Makefile is also included:

```text
make
```

## Run

Windows PowerShell:

```text
.\line_editor.exe
```

Linux or macOS:

```text
./line_editor
```

At the prompt, type `help` for the command summary. See [HELP.md](HELP.md) for full usage examples.
