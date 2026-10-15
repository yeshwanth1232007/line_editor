#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LENGTH 500

char *lines[MAX_LINES];
int line_count = 0;


/* Remove newline character from a string */
void remove_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}


/* Clear the input buffer */
void clear_input_buffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* discard extra characters */
    }
}


/* Insert a new line */
void insert_line(int position, const char *text)
{
    int i;

    if (line_count >= MAX_LINES)
    {
        printf("Error: Document is full.\n");
        return;
    }

    if (position < 1 || position > line_count + 1)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /*
       Shift existing lines one position down.
       We start from the last line.
    */
    for (i = line_count; i >= position; i--)
    {
        lines[i] = lines[i - 1];
    }

    /* Allocate memory for the new line */
    lines[position - 1] = malloc(strlen(text) + 1);

    if (lines[position - 1] == NULL)
    {
        printf("Error: Memory allocation failed.\n");

        /* Undo the shifting */
        for (i = position - 1; i < line_count; i++)
        {
            lines[i] = lines[i + 1];
        }

        return;
    }

    strcpy(lines[position - 1], text);

    line_count++;

    printf("Line inserted successfully.\n");
}


/* Delete a line */
void delete_line(int position)
{
    int i;

    if (line_count == 0)
    {
        printf("Document is empty.\n");
        return;
    }

    if (position < 1 || position > line_count)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Free memory used by the deleted line */
    free(lines[position - 1]);

    /*
       Shift all lines after the deleted line upward.
    */
    for (i = position - 1; i < line_count - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lines[line_count - 1] = NULL;

    line_count--;

    printf("Line deleted successfully.\n");
}


/* Display all lines */
void display_document()
{
    int i;

    if (line_count == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (i = 0; i < line_count; i++)
    {
        printf("%d. %s\n", i + 1, lines[i]);
    }

    printf("--------------------\n");
}


/* Save document to a file */
void save_file(const char *filename)
{
    FILE *file;
    int i;

    file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    for (i = 0; i < line_count; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);

    printf("Document saved to %s\n", filename);
}


/* Load document from a file */
void load_file(const char *filename)
{
    FILE *file;
    char buffer[MAX_LENGTH];

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Could not open %s\n", filename);
        return;
    }

    /* Clear the current document */
    while (line_count > 0)
    {
        free(lines[line_count - 1]);
        lines[line_count - 1] = NULL;
        line_count--;
    }

    /* Read each line from the file */
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        remove_newline(buffer);

        if (line_count >= MAX_LINES)
        {
            printf("Maximum line limit reached.\n");
            break;
        }

        lines[line_count] = malloc(strlen(buffer) + 1);

        if (lines[line_count] == NULL)
        {
            printf("Memory allocation failed.\n");
            break;
        }

        strcpy(lines[line_count], buffer);

        line_count++;
    }

    fclose(file);

    printf("Document loaded from %s\n", filename);
}


/* Search for a word or phrase */
void search_document(const char *word)
{
    int i;
    int found = 0;

    if (line_count == 0)
    {
        printf("Document is empty.\n");
        return;
    }

    for (i = 0; i < line_count; i++)
    {
        if (strstr(lines[i], word) != NULL)
        {
            printf("Found on line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("'%s' was not found.\n", word);
    }
}


/* Count lines and words */
void show_statistics()
{
    int i;
    int word_count = 0;
    int in_word;

    for (i = 0; i < line_count; i++)
    {
        char *p = lines[i];
        in_word = 0;

        while (*p != '\0')
        {
            if (isspace((unsigned char)*p))
            {
                in_word = 0;
            }
            else if (!in_word)
            {
                word_count++;
                in_word = 1;
            }

            p++;
        }
    }

    printf("\n----- STATISTICS -----\n");
    printf("Number of lines : %d\n", line_count);
    printf("Number of words : %d\n", word_count);
    printf("----------------------\n");
}


/* Display help */
void show_help()
{
    printf("\n========== HELP ==========\n");

    printf("insert <line> <text>\n");
    printf("  Insert text at a line number.\n");
    printf("  Example: insert 1 Hello World\n\n");

    printf("delete <line>\n");
    printf("  Delete a line.\n");
    printf("  Example: delete 2\n\n");

    printf("display\n");
    printf("  Display the entire document.\n\n");

    printf("save <filename>\n");
    printf("  Save document to a text file.\n");
    printf("  Example: save document.txt\n\n");

    printf("load <filename>\n");
    printf("  Load a text file.\n");
    printf("  Example: load document.txt\n\n");

    printf("search <word>\n");
    printf("  Search for a word or phrase.\n");
    printf("  Example: search programming\n\n");

    printf("stats\n");
    printf("  Show line and word count.\n\n");

    printf("help\n");
    printf("  Show this help menu.\n\n");

    printf("quit\n");
    printf("  Exit the editor.\n");

    printf("==========================\n");
}


/* Free all allocated memory */
void cleanup()
{
    int i;

    for (i = 0; i < line_count; i++)
    {
        free(lines[i]);
        lines[i] = NULL;
    }

    line_count = 0;
}


/* Main function */
int main()
{
    char input[MAX_LENGTH];
    int position;
    char text[MAX_LENGTH];
    char filename[100];

    printf("=================================\n");
    printf("       SIMPLE LINE EDITOR\n");
    printf("=================================\n");

    printf("Type 'help' to see available commands.\n");

    while (1)
    {
        printf("\n> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        remove_newline(input);

        if (strlen(input) == 0)
        {
            continue;
        }


        /* INSERT command */
        if (strncmp(input, "insert ", 7) == 0)
        {
            if (sscanf(input, "insert %d %[^\n]", &position, text) == 2)
            {
                insert_line(position, text);
            }
            else
            {
                printf("Usage: insert <line> <text>\n");
            }
        }


        /* DELETE command */
        else if (sscanf(input, "delete %d", &position) == 1)
        {
            delete_line(position);
        }


        /* DISPLAY command */
        else if (strcmp(input, "display") == 0)
        {
            display_document();
        }


        /* SAVE command */
        else if (sscanf(input, "save %99s", filename) == 1)
        {
            save_file(filename);
        }


        /* LOAD command */
        else if (sscanf(input, "load %99s", filename) == 1)
        {
            load_file(filename);
        }


        /* SEARCH command */
        else if (strncmp(input, "search ", 7) == 0)
        {
            if (strlen(input + 7) > 0)
            {
                search_document(input + 7);
            }
            else
            {
                printf("Usage: search <word>\n");
            }
        }


        /* STATISTICS command */
        else if (strcmp(input, "stats") == 0)
        {
            show_statistics();
        }


        /* HELP command */
        else if (strcmp(input, "help") == 0)
        {
            show_help();
        }


        /* QUIT command */
        else if (strcmp(input, "quit") == 0)
        {
            printf("Exiting editor...\n");
            break;
        }


        /* Invalid command */
        else
        {
            printf("Unknown command. Type 'help' for available commands.\n");
        }
    }

    cleanup();

    return 0;
}