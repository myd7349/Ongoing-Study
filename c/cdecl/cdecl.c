#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../error.h"
#include "../stack.h"


#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define MAX_TOKEN_LEN (256)
#define MAX_TOKENS    (256)
#define MAX_LINE_LEN  (1024)


typedef enum
{
    TOKEN_TYPE,
    TOKEN_QUALIFIER,
    TOKEN_IDENTIFIER,
    TOKEN_SINGULAR_CHAR,
} token_type_t;


typedef struct
{
    token_type_t type;
    char string[MAX_TOKEN_LEN + 1];
} token_t;


stack_init(token_t, tokens, MAX_TOKENS);

static token_t this;


static const char *skip_white_spaces(const char *str)
{
    assert(str != NULL);

    while (*str != '\0' && isspace(*str))
        ++str;

    return str;
}


static char classify_string(const char *token)
{
    static const char *known_types[] =
    {
        "signed",
        "unsigned",
        "void",
        "char",
        "short",
        "int",
        "long",
        "float",
        "double",
        "struct",
        "union",
        "enum",
    };

    static const char *known_qualifiers[] =
    {
        "const",
        "volatile",
        "restrict",
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(known_types); ++i)
    {
        if (strcmp(token, known_types[i]) == 0)
            return TOKEN_TYPE;
    }

    for (i = 0; i < ARRAY_SIZE(known_qualifiers); ++i)
    {
        if (strcmp(token, known_qualifiers[i]) == 0)
            return TOKEN_QUALIFIER;
    }

    return TOKEN_IDENTIFIER;
}


static const char *get_token(const char *gibberish)
{
    const char *p = skip_white_spaces(gibberish);
    const char *q = NULL;
    size_t token_length;

    if (*p == '\0')
        return p;

    if (isalnum(*p) || *p == '_')
    {
        q = p + 1;
        while (isalnum(*q) || *q == '_')
            ++q;

        token_length = q - p;
        if (token_length > MAX_TOKEN_LEN)
            error("Token is too long!\n");

        strncpy(this.string, p, token_length);
        this.string[token_length] = '\0';
        this.type = classify_string(this.string);

        return q;
    }
    else
    {
        this.string[0] = *p;
        this.string[1] = '\0';
        this.type = TOKEN_SINGULAR_CHAR;

        return p + 1;
    }
}


static const char *read_to_first_identifier(const char *gibberish)
{
    const char *p = get_token(gibberish);

    while (*p != '\0')
    {
        if (this.type == TOKEN_IDENTIFIER)
        {
            printf("`%s` is ", this.string);
            break;
        }

        if (stack_is_full(tokens))
            error("Too many tokens!\n");

        stack_push(tokens, this);

        p = get_token(p);
    }

    return p;
}


static const char *deal_with_arrays(const char *gibberish)
{
    const char *p = get_token(gibberish);
    if (this.type == TOKEN_SINGULAR_CHAR && this.string[0] == ']')
    {
        printf("array of ");
        return p;
    }
    else
    {
        printf("array[%s] of ", this.string);

        p = get_token(p);
        if (this.type != TOKEN_SINGULAR_CHAR || this.string[0] != ']')
            error("[ expected!\n");

        return p;
    }
}


static const char *deal_with_function_args(const char *gibberish)
{
    const char *p = gibberish;

    int left_brackets = 0;

    while (*p != '\0')
    {
        p = get_token(p);

        if (this.type == TOKEN_SINGULAR_CHAR)
        {
            if (this.string[0] == '(')
            {
                left_brackets += 1;
            }
            else if (this.string[0] == ')')
            {
                if (left_brackets > 0)
                    left_brackets -= 1;
                else
                    break;
            }
        }
    }

    printf("function returning ");

    return p;
}


static void deal_with_any_pointers()
{
    while (!stack_is_empty(tokens)
        && stack_top(tokens).type == TOKEN_SINGULAR_CHAR
        && stack_top(tokens).string[0] == '*')
    {
        printf("pointer to ");
        stack_pop(tokens);
    }
}


static const char *deal_with_declarator(const char *gibberish)
{
    const char *p = get_token(gibberish);

    if (this.type == TOKEN_SINGULAR_CHAR)
    {
        if (this.string[0] == '[')
        {
            p = deal_with_arrays(p);
        }
        else if (this.string[0] == '(')
        {
            p = deal_with_function_args(p);
        }
        else
        {
            p -= 1; // ungetchar
        }
    }

    deal_with_any_pointers();

    while (!stack_is_empty(tokens))
    {
        if (stack_top(tokens).type == TOKEN_SINGULAR_CHAR && stack_top(tokens).string[0] == '(')
        {
            stack_pop(tokens);
            p = get_token(p);
            assert(this.type == TOKEN_SINGULAR_CHAR && this.string[0] == ')');
            p = deal_with_declarator(p);
        }
        else
        {
            printf("%s", stack_top(tokens).string);
            stack_pop(tokens);

            if (stack_is_empty(tokens))
                printf(".\n");
            else
                putchar(' ');
        }
    }

    return p;
}


static void c_gibberish_to_english(const char *gibberish)
{
    const char *p = read_to_first_identifier(gibberish);
    deal_with_declarator(p);
}


static void process_file(FILE *fp)
{
    char line[MAX_LINE_LEN];

    assert(fp != NULL);

    while (fgets(line, MAX_LINE_LEN, fp) != NULL)
        c_gibberish_to_english(line);
}


int main(int argc, char *argv[])
{
    FILE *fp = stdin;

    if (argc == 2)
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            perror("Failed to open file with fopen");
            exit(EXIT_FAILURE);
        }

        process_file(fp);

        fclose(fp);
    }
    else
    {
        process_file(stdin);
    }

    // PASS:
    // char (*p)[10];
    // char *p[10]
    // char * const * (*next)()
    // char *(*c[10])(int **p)
    // void (*signal(int sig, void(*func)(int)))(int)
    // int (*(*foo)(void ))[3]
    // char *(*fptab[])()
    // double **data;
    // const double **data;
    // double * const *data;
    /*
    double **data = ...;
    
    void SaveData(const double **data, size_t rows, size_t cols); // this one?
    or:
    void SaveData(double * const *data, size_t rows, size_t cols); // this one?
    */

    // const int *foo
    // int * const foo
    // int X::*foo
    // class Y *(X::*foo)(arg1, arg2)
    // void (* x)(int (*[])())
    // const int * volatile * (**const volatile arr[6666]) [2333]

    return 0;
}


// References:
// Expert C Programming: Deep C Secrets, Ch3.8, Ch8
// https://linux.die.net/man/1/cdecl
// https://cdecl.org/
// https://github.com/aartamonau/cdecl
// https://ioccc.org/1988/reddy.c
// https://stackoverflow.com/questions/10091825/constant-pointer-vs-pointer-on-a-constant-value
// https://www.zhihu.com/question/439224121
// https://github.com/ridiculousfish/cdecl-blocks
