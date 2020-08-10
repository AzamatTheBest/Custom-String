#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    char *str;
    unsigned length;
    unsigned how_much;
} string_t;

string_t *create_string(char *str);
unsigned compute_len(char *str);
void print_string(string_t *string, FILE *out);

int main(int argc, char const *argv[])
{
    string_t *var = create_string("No more heros");
    print_string(var, stdout);
    printf("\n");
    return 0;
}

unsigned compute_len(char *str)
{
    int i = 0;
    while(*(str++))
    {
        i++;
    }
    return i;
}

string_t *create_string(char *str)
{
    string_t *string = malloc(sizeof(string_t));
    string->length = compute_len(str);
    string->str = malloc(string->length);
    string->how_much = 0;

    while(*(str))
    {
        *(string->str++) = *(str++);
    }
    string->str -= string->length;

    return string;
}

void print_string(string_t *string, FILE *out)
{
    fwrite(string->str, sizeof(char), string->length, out);
}
