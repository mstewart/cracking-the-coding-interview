/*
 * Replace all the spaces in a string with "%20".
 */

#include <string>
#include <algorithm>
#include <assert.h>

using std::string;


string url_encode_spaces(const string& s)
{
    string buffer;

    string::const_iterator it = s.begin(),
                           end = s.end();
    while (true)
    {
        string::const_iterator next_space = std::find(it, end, ' ');
        buffer.append(it, next_space);

        if (next_space == end) {
            break;
        } else {
            buffer.append("%20");
            it = next_space + 1;
        }
    }

    return buffer;
}


int main()
{
    assert( url_encode_spaces("") == "" );
    assert( url_encode_spaces("a") == "a" );
    assert( url_encode_spaces("abcdef") == "abcdef" );

    assert( url_encode_spaces(" ") == string("%20") );
    assert( url_encode_spaces("x ") == string("x%20") );
    assert( url_encode_spaces("x  x ") == string("x%20%20x%20") );
    assert( url_encode_spaces("abc def") == string("abc%20def") );
}
