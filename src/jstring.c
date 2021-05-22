#include "headers/jstring.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void fatal(string **message)
{
    string_concat(message, "\n\0");
    perror((*message)->value);
    exit(-1);
}
void *err_malloc(size_t size)
{
    void *ptr = malloc(size);
    if(ptr == NULL)
    {
        string *message = create_string("Could not malloc memory");
        fatal(&message);
    }
    return ptr;
}
void *err_realloc(void *ptr, size_t size)
{
    ptr = realloc(ptr, size);
    if(ptr == NULL)
    {
        string *message = create_string("Could not realloc memory");
        fatal(&message);
    }
    return ptr;
}
void err_free(void *ptr)
{
    if(ptr == NULL)
    {
        return;
    }
    free(ptr);
    ptr = NULL;
}

//Actual library code

string *create_string(const char *value)
{
    string *str;
    if(value == NULL)
    {
        return NULL;
    }
    str = (string *)err_malloc(sizeof(string));
    str->value = NULL;
    str->length = 0;
    str->length = string_length(value);
    string_copy(&str, value);
    return str;
}

void destroy_string(string **str)
{
    err_free((*str)->value);
    err_free(*str);
}

int string_length(const char *str)
{
    int length = 0;
    if(str == NULL)
    {
        return 0;
    }
    while(*str != '\0')
    {
        ++str;
        ++length;
    }
    return length+1;
}

int index_of(const string **str, const char *substring, const int n)
{
    int index = n, sub_length = string_length(substring), connected_chars = 0;
    for(;index < (*str)->length; ++index)
    {
        if((*str)->value[index] == substring[index])
        {
            ++connected_chars;
        }
        else
        {
            connected_chars = 0;
        }
        ++index;
        if(connected_chars == sub_length)
        {
            return index;
        }
    }
    return -1;
}
int string_compare(const string **str, const char *str2)
{
    if((*str)->length != string_length(str2))
    {
        return 0;
    }
    for(int i = 0; i < (*str)->length; ++i)
    {
        if((*str)->value[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}

void string_copy(string **destination, const char *source)
{
    int length = string_length(source);
    (*destination)->value = (char*) err_malloc(sizeof(char) * length);
    for(int i = 0; i < length; ++i)
    {
        (*destination)->value[i] = source[i];
    }
    (*destination)->value[(*destination)->length - 1] = '\0';
}

void string_concat(string **destination, const char *source)
{
    int src_length = string_length(source), i = (*destination)->length - 1, j = 0;
    (*destination)->value = (char*) err_realloc((*destination)->value, sizeof(char) * ((*destination)->length * src_length));
    (*destination)->length += src_length;
    for(; i < (*destination)->length; ++i)
    {
        (*destination)->value[i] = source[j];
        ++j;
    }
    (*destination)->value[(*destination)->length - 1] = '\0';
}
//To be implemented

/*

string *str_insert(string *destination, string *source, int index)
{
    int dest_length = str_length(destination);
    if(index > dest_length)
    {
        fatal("Index is greater than the size of destination");
    }
    string *new_str = (char*) err_malloc(sizeof(char));
    int length = 1;
    int i = 0;
    while(i < index)
    {
        new_str = (char*) err_realloc(new_str, sizeof(char) * ++length);
        *(new_str++) = *destination++;
        ++i;
    }
    str_concat(new_str, source);
    while(*destination != '\0')
    {
        new_str = (char*) err_realloc(new_str, sizeof(char) * ++length);
        *(new_str++) = *destination++;
    }
    new_str[length - 1] = '\0';
    return new_str;
}
string *substr(string *str, int start, int end)
{
    int str_len = str_length(str);
    if(start >= str_len || end > str_len)
    {
        fatal("Trying to reference data that doesn't exist in the str");
    }
    string *sub = (char*) err_malloc(sizeof(char) * (end - start - 1));
    for(int i = start; i < end; ++i)
    {
        *(sub++) = str[i];
    }
    sub[str_length(sub) - 1] = '\0';
    return sub;
}
string *str_remove(string *str, string *to_remove)
{
    if(index_of(str, to_remove) == -1)
    {
        fatal("str does not exist withing str, could not remove");
    }
    int remove_len = str_length(to_remove), index = 0, stop_at = index_of(str, to_remove);
    string *new_str = (char*) err_malloc(sizeof(char));
    while(*str != '\0')
    {
        if(index == stop_at)
        {
            index += remove_len;
        }
        *(new_str++) = str[index++];
    }
    new_str[(str_length(str) - remove_len) - 1] = '\0';
    return new_str;
}
int parse_int(const string *str)
{
    int multiplier = 0;
    int number = 0;
    for(int i = str_length(str) - 1; i >= 0; --i)
    {
        if(!isdigit(str[i]))
        {
            fatal("Must be of type integer");
        }
        switch(str[i])
        {
            case '0': number += 0 * multiplier; break;
            case '1': number += 1 * multiplier; break;
            case '2': number += 2 * multiplier; break;
            case '3': number += 3 * multiplier; break;
            case '4': number += 4 * multiplier; break;
            case '5': number += 5 * multiplier; break;
            case '6': number += 6 * multiplier; break;
            case '7': number += 7 * multiplier; break;
            case '8': number += 8 * multiplier; break;
            case '9': number += 9 * multiplier; break;
        }
        multiplier += 10;
    }
    return number;
}
string *int_to_sting(int number)
{
    string *reverse = (char*) err_malloc(sizeof(char)), *str, buffer;
    while(number >= 0)
    {
        switch(number % 10)
        {
            case 0: buffer = '0'; break;
            case 1: buffer = '1'; break;
            case 2: buffer = '2'; break;
            case 3: buffer = '3'; break;
            case 4: buffer = '4'; break;
            case 5: buffer = '5'; break;
            case 6: buffer = '6'; break;
            case 7: buffer = '7'; break;
            case 8: buffer = '8'; break;
            case 9: buffer = '9'; break;
        }
        str_concat(reverse, &buffer);
        number /= 10;
    }
    int length = str_length(reverse);
    str = (char*) err_malloc(str_length(reverse));
    for(int i = length - 1; i >= 0; --i)
    {
        str_concat(str, &reverse[i]);
    }
    str[length - 1] = '\0';
    free(reverse);
    return str;
}
string *to_lower(const string *str)
{
    while(*str != '\0')
    {
        if(isalpha(*str))
        {
            switch(*str)
            {
                case 'A': *str = 'a'; break;
                case 'B': *str = 'b'; break;
                case 'C': *str = 'c'; break;
                case 'D': *str = 'd'; break;
                case 'E': *str = 'e'; break;
                case 'F': *str = 'f'; break;
                case 'G': *str = 'g'; break;
                case 'H': *str = 'h'; break;
                case 'I': *str = 'i'; break;
                case 'J': *str = 'j'; break;
                case 'K': *str = 'k'; break;
                case 'L': *str = 'l'; break;
                case 'M': *str = 'm'; break;
                case 'N': *str = 'n'; break;
                case 'O': *str = 'o'; break;
                case 'P': *str = 'p'; break;
                case 'Q': *str = 'q'; break;
                case 'R': *str = 'r'; break;
                case 'S': *str = 's'; break;
                case 'T': *str = 't'; break;
                case 'U': *str = 'u'; break;
                case 'V': *str = 'v'; break;
                case 'W': *str = 'w'; break;
                case 'X': *str = 'x'; break;
                case 'Y': *str = 'y'; break;
                case 'Z': *str = 'z'; break;
            }
        }
        ++(*str);
    }
}
string *to_upper(const string *source)
{
    char str[] = *source;
    while(*str != '\0')
    {
        if(isalpha(*str))
        {
            switch(*str)
            {
                case 'a': *str = 'A'; break;
                case 'b': *str = 'B'; break;
                case 'c': *str = 'C'; break;
                case 'd': *str = 'D'; break;
                case 'e': *str = 'E'; break;
                case 'f': *str = 'F'; break;
                case 'g': *str = 'G'; break;
                case 'h': *str = 'H'; break;
                case 'i': *str = 'I'; break;
                case 'j': *str = 'J'; break;
                case 'k': *str = 'K'; break;
                case 'l': *str = 'L'; break;
                case 'm': *str = 'M'; break;
                case 'n': *str = 'N'; break;
                case 'o': *str = 'O'; break;
                case 'p': *str = 'P'; break;
                case 'q': *str = 'Q'; break;
                case 'r': *str = 'R'; break;
                case 's': *str = 'S'; break;
                case 't': *str = 'T'; break;
                case 'u': *str = 'U'; break;
                case 'v': *str = 'V'; break;
                case 'w': *str = 'W'; break;
                case 'x': *str = 'X'; break;
                case 'y': *str = 'Y'; break;
                case 'z': *str = 'Z'; break;
            }
        }
        ++(*str);
    }
    string *ret = create_string((const char *)str);
    return ret;
}

*/
