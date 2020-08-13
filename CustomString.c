#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    char *str;
    unsigned length;
} string_t;


string_t *create_string(char *str);
string_t *concat_strings(string_t *string1, string_t *string2);
string_t *get_slice(string_t *string, int first, int second);
string_t *string_dup(string_t *string);
unsigned compute_len(char *str);
unsigned string_compare(string_t *string1, string_t *string2);
int find_substring(string_t *string, char *substring);
void string_replace(string_t *string, string_t *old, string_t *new);
void string_append(string_t *string, char *str);
void print_string(string_t *string, FILE *out);

void test(void);


int main(int argc, char const *argv[])
{
    test();

    return 0;
}

void test()
{
    string_t *var = create_string("No more heros");
    string_t *another = create_string("anymore in this life");
    string_t *one_more = concat_strings(var, another);
    string_t *slice = get_slice(var, 1, 60);
    string_t *new = string_dup(var);

    string_t *ab = create_string("or");
    string_t *ba = create_string("boy next door");


    print_string(new, stdout);
    
    printf("\n");
    string_replace(var, ab, ba);
    print_string(var, stdout);
    printf("\n");
    print_string(new, stdout);
    printf("\n");
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

string_t *concat_strings(string_t *string1, string_t *string2)
{
    string_t *new_string;
    char str[string1->length + string2->length];
    int i;

    for (i = 0; i < string1->length; i++)
    {
        str[i] = string1->str[i];
    }

    for (; i < string1->length + string2->length; i++)
    {
        str[i] = string2->str[i - string1->length]; 
    }
    str[i] = '\0';
    new_string = create_string(str);

    return new_string;
}

string_t *get_slice(string_t *string, int index1, int index2)
{
    char *str;
    string_t *string_slice;
    int i, j = 0;

    if (index1 < 0 && index2 > string->length - 1)
    {
        return string;
    }
    else if (index1 < 0)
    {
        str = malloc(index2 + 1);
        for (i = 0; i < index2; i++)
        {
            str[j++] = string->str[i];
        }
    }   
    else if (index2 > string->length - 1)
    {
        str = malloc(string->length - index1);
        for (i = index1; i < string->length; i++)
        {
            str[j++] = string->str[i];
        }
    }
    else
    {
        str = malloc(index2 + 1 - index1);
        for (i = index1; i < index2; i++)
        {
            str[j++] = string->str[i];
        }
    }
    str[j] = '\0';
    string_slice = create_string(str);

    return string_slice;
}

string_t *string_dup(string_t *string)
{
    string_t *another_string = create_string(string->str);
    return another_string; 
}

void string_append(string_t *string, char *str)
{
    unsigned len = compute_len(str);
    unsigned i;
    string->length += len;
    string->str = realloc(string->str, string->length);
    string->str += (string->length - len);

    for (i = 0; str[i] != '\0'; i++)
        *(string->str++) = str[i];

    *string->str = '\0';
    string->str -= string->length;
}

int find_substring(string_t *string, char *substring)
{
    unsigned i, v;
    unsigned len = compute_len(substring);
    unsigned flag;

    for (i = 0; string->str[i]; i++)
    {
        flag = 1;
        for (v = i; *substring; v++, substring++)
        {
            if (*substring != string->str[v])
            {
                flag = 0;
            }
        }
        if (flag == 1)
            return i;
        substring -= len;
    }

    return -1;
}

/*
    Bad implementation of replace 
*/
void string_replace(string_t *string, string_t *old, string_t *new)
{
    string_t *temp = string; 
    temp->length = temp->length - old->length + new->length;
    temp->str = realloc(temp->str, temp->length);  
    char *temp_to_change = malloc(temp->length);
    unsigned index_of_old = find_substring(temp, old->str);
    unsigned i, v, c;

    for (i = c = 0; temp->str[c];)
    {
        if (i == index_of_old)
        {
            for (v = 0; new->str[v]; v++)
            {
                temp_to_change[i++] = new->str[v];
            }
            c += old->length;
        }
        else
        {
            temp_to_change[i++] = temp->str[c++];
        }
        
    }

    for (i = 0; temp_to_change[i]; i++)
    {
        temp->str[i] = temp_to_change[i];
    }
    temp->str[i] = '\0';
}

unsigned string_compare(string_t *string1, string_t *string2)
{
    unsigned char uc1, uc2;

    while(*(string1->str) != '\0' && *(string1->str) == *(string2->str)
    {
        string1->str++;
        string2->str++;
    }

    uc1 = (*(unsigned char *) string1->str);
    uc2 = (*(unsigned char *) string2->str);

    return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}
