
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct _token
{
    char* content;
    uint32_t size;

    uint32_t src_line;

    struct _token* next;
    struct _token* prev;
}* token_t;


enum token_type_t
{
    TOKEN_TYPE_INVALID,
    TOKEN_TYPE_ALPHA,
    TOKEN_TYPE_NUM,
    TOKEN_TYPE_QUOTE,
    TOKEN_TYPE_SPACE,
    TOKEN_TYPE_NEWLINE,
    TOKEN_TYPE_SYM,
};


enum token_type_t get_token_type(char c)
{
    /**/ if (isalpha(c)) return TOKEN_TYPE_ALPHA;
    else if (isdigit(c)) return TOKEN_TYPE_NUM;
    else if (c == '"'  ) return TOKEN_TYPE_QUOTE;
    else if (c == ' '  ) return TOKEN_TYPE_SPACE;
    else if (c == '\n' ) return TOKEN_TYPE_NEWLINE;
    else                 return TOKEN_TYPE_SYM;
}





token_t lex(char* src_path)
{
    FILE* f = fopen(src_path, "r");
    if (!f)
    {
        printf("unable to open file: %s\n", src_path);
        exit(1);
    }

    enum token_type_t state = TOKEN_TYPE_INVALID;
    enum token_type_t type;
    char buffer[128];
    char* ptr = buffer;

    struct _token hook;
    token_t last = &hook;

    char c;
    uint32_t line = 1;
    bool string = false;
    while ((c = fgetc(f)) != EOF)
    {
        type = get_token_type(c);

        if (state == TOKEN_TYPE_QUOTE)
            string = !string;

        if (type == TOKEN_TYPE_NEWLINE)
            line++;

        if ((state == type && type != TOKEN_TYPE_SYM) || string)
            *ptr++ = c;

        else
        {
            //finish last token
            *ptr = '\0';

            //capture token
            if (
                //state != TOKEN_TYPE_NEWLINE && 
                //state != TOKEN_TYPE_SPACE && 
                state != TOKEN_TYPE_INVALID
            ) //filter token capture
            {
                token_t node = calloc(1, sizeof(struct _token));             
                node->content = strdup(buffer);
                node->size = strlen(buffer);
                node->src_line = line;
            
                //link
                node->prev = last;
                last->next = node;
                last = node;
            }

            //initialize buffer for next token
            ptr = buffer;
            *ptr++ = c;
        }

        state = type;
    }


    token_t t = hook.next;
    for (; t; t = t->next)
        printf("%d %d %s\n", t->src_line, t->size, t->content);


    return hook.next;
}

