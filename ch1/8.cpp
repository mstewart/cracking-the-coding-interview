/*
 * Given a method isSubstring(s1,s2) :: bool,
 * write code to check if s2 is a rotation of s1
 * using only one call to isSubstring.
 */


#include <string>

using std::string;

/*
 * Solution is straightforward:
 * take the word s2 to be tested, concatenate it with itself,
 * then check if s1 is a substring of that.
 */
bool
isSubstring(string const& needle, string const& haystack)
{
    return true; // dummy impl
}

bool is_rotation(string const& s1, string const& s2)
{
    const string doubled(s2 + s2);

    return isSubstring(s1, doubled);
}
