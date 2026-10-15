# Line Editor Help

Run the editor and type commands at the `>` prompt. Line numbers start at 1.

## `insert <line> <text>`
Inserts a new line at the specified position.

Example:

```text
insert 1 Hello, world!
```

## `delete <line>`
Deletes the line at the specified position.

Example:

```text
delete 1
```

## `display`
Displays every line in the current document with its line number.

Example:

```text
display
```

## `save <filename>`
Writes the current document to a text file.

Example:

```text
save document.txt
```

## `load <filename>`
Replaces the current document with the contents of a text file.

Example:

```text
load document.txt
```

## `search <word or phrase>`
Finds and displays every line containing the requested text.

Example:

```text
search programming
```

## `stats`
Displays the number of lines and words in the current document.

Example:

```text
stats
```

## `help`
Displays the built-in command summary.

Example:

```text
help
```

## `quit`
Exits the editor and releases allocated memory.

Example:

```text
quit
```
