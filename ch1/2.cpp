/*
 * Reverse a C-style string.
 */

#include <cstring>
#include <assert.h>
#include <string>

inline void swap_chars(char* x, char* y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

void reverse_string(char* s)
{
    size_t len = std::strlen(s);

    for (size_t i = 0;
            i < len/2;
            ++i)
    {
        swap_chars(s + i, s + len - i - 1);
    }
}

int main()
{
    char s[] = "foo";
    reverse_string(s);
    assert( std::string("oof") == std::string(s) );

    char empty[] = "";
    reverse_string(empty);
    assert( std::string() == std::string(empty) );
}
