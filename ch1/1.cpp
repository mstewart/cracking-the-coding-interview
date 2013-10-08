/*
 * Determine if a string has all unique characters.
 *
 * Avoid using any additional data structures.
 */

#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

bool hasOnlyUniqueCharacters(string& s)
{
    // sort in-place, then check for consecutive duplicates.
    sort(s.begin(), s.end());

    for (string::iterator it = s.begin(),
                          end = s.end();
        it != end;
        ++it)
    {
        string::iterator next = it + 1;
        if (next != end && *it == *next) {
            return false;
        }
    }

    return true;
}

int main()
{
    string blank(""), singleton("x"), uniq1("cat"), uniq2("abcdefg"), dup1("foo"), dup2("canada");

    assert( hasOnlyUniqueCharacters(blank) );
    assert( hasOnlyUniqueCharacters(singleton) );
    assert( hasOnlyUniqueCharacters(uniq1) );
    assert( hasOnlyUniqueCharacters(uniq2) );

    assert( ! hasOnlyUniqueCharacters(dup1) );
    assert( ! hasOnlyUniqueCharacters(dup2) );
}
