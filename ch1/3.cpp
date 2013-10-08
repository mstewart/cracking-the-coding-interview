/*
 * Remove duplicate characters from a string, in O(1) space.
 */


#include <set>
#include <cstring>
#include <string>
#include <assert.h>
#include <algorithm>
#include <iostream>


using namespace std;


void remove_duplicate_characters(char* s)
{
    const size_t len = strlen(s);

    // This could be a lookup table of length 256, i.e. sizeof(char),
    // of type bool[], which would be more efficient.
    // But either way is O(1) space.
    set<char> encountered;

    size_t num_deleted = 0;
    for(char* it = s;
            it < s + len - num_deleted;
            ++it)
    {
        if (encountered.count(*it)) {
            // Delete char, pushing subsequent chars forward
            *it = '\0';
            rotate(it, it + 1, s + len - num_deleted);
            ++num_deleted;
        } else {
            encountered.insert(*it);
        }
    }
}


int main()
{
    char empty[] = "",
         single[] = "x",
         foo[] = "foo",
         canada[] = "canada";

    remove_duplicate_characters(empty);
    remove_duplicate_characters(single);
    remove_duplicate_characters(foo);
    remove_duplicate_characters(canada);

    assert( string() == string(empty) );
    assert( string("x") == string(single) );
    assert( string("fo") == string(foo) );
    assert( string("cand") == string(canada) );
}
