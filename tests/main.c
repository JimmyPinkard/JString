#include <jstring.h>
#include <stdio.h>

int main()
{
    string *str = create_string("Hello World!");
    printf("%s is %i chars long\n", str->value, str->length);
    string_concat(&str, "\nIt's me Jimmy!");
    printf("%s is %i chars long\n", str->value, str->length);
    destroy_string(&str);
    return 0;
}
