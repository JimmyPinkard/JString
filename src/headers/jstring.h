#ifndef JSTRING_JSTRING_H
#define JSTRING_JSTRING_H

/*
 * String struct
 * char *value - can be called by derefrencing the string pointer
 * int length - used to keep up with the length and add null terminator
 */
typedef struct string
{
    char *value;
    int length;
}string;

//get the length of a string
int string_length(const char *string);

//get the index of the substring's occurence after n
int index_of(const string **str, const char *substring, const int n);

//compare two strings
int string_compare(const string **str, const char *str2);

//creates a string struct
string *create_string(const char *value);

//destorys a string struct
void destroy_string(string **str);

//copy a string into the string struct
void string_copy(string **destination, const char *source);

//string concatenation
void string_concat(string **destination, const char *source);

/*

//copies into a string using a format string
void stringf(const char *format, string *str, ...);

//inserts source into a string at a particular index
void string_insert(string *destination, const char *source, const int index);

//gets a substring between start and and end (exclusive)
string *substring(const string *str, const int start, const int end);

//removes part of a string between start and end (exclusive)
void string_remove(string *str, const int start, const int end);

//turns a string into an integer
int parse_int(const string *str);

//turns an int into a string
string *int_to_sting(const int number);

//returns the string as all lowercase
string *to_lower(const string *str);

//returns the string as all upercase
string *to_upper(const string *source);

*/

//Maybe adds

/*
* Read file and read file until?
*/

#endif //JSTRING_JSTRING_H
