/*
 * Remove duplicates from an unsorted LL.
 */


#include <set>
#include <vector>
#include <iostream>
#include <assert.h>

#include "list.h"

using namespace std;

template<typename T>
void
remove_duplicates( Node<T>* head )
{
    typedef Node<T> N;

    // Special-case empty list handling,
    // so that we can avoid special-handling the first node
    // inside the loop body.
    if (head == NULL) {
        return;
    }

    set<T>  encountered;
    encountered.insert(head->elem);

    // Loop invariants:
    //  it walks through the original list,
    //  tail->next always points to it.
    N*  tail = head;
    N*  it = tail->next;
    while (it != NULL) {
        if (encountered.count(it->elem)) {
            it = tail->next = it->next;
        } else {
            encountered.insert(it->elem);
            tail = it;
            it = it->next;
        }
    }
}


int main()
{
    int ints[] = {1,2,3,4,3,70};
    vector<int> vec(ints, ints + sizeof(ints) / sizeof(int));

    Node<int>* list = make_list(vec.begin(), vec.end());

    assert( list->elem == 1 );
    assert( list->next->elem == 2 );
    assert( list->next->next->elem == 3 );
    assert( list->next->next->next->elem == 4 );

    remove_duplicates(list);
    assert( list->elem == 1 );
    assert( list->next->elem == 2 );
    assert( list->next->next->elem == 3 );
    assert( list->next->next->next->elem == 4 );
    assert( list->next->next->next->next->elem == 70 );
    assert( list->next->next->next->next->next == NULL );
}
