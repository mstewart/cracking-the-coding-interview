/*
 * Determine whether 2 strings are anagrams.
 */


#include <string>
#include <algorithm>
#include <assert.h>

using std::string;


bool is_anagram(const string& s1,
                const string& s2)
{
    string c1(s1), c2(s2);

    std::sort(c1.begin(), c1.end());
    std::sort(c2.begin(), c2.end());

    return c1 == c2;
}


int main()
{
    assert( is_anagram("", "") );
    assert( is_anagram("x", "x") );
    assert( is_anagram("foo", "ofo") );
    assert( is_anagram("banana", "nanaab") );
    assert( is_anagram("enter_dragon", "gonad_enterr") );

    assert( ! is_anagram("", "x") );
    assert( ! is_anagram("y", "x") );
    assert( ! is_anagram("x", "xx") );
    assert( ! is_anagram("mauritius", "ethiopia") );
    assert( ! is_anagram("FOO", "foo") );
}
