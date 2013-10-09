/*
 * Delete a node in the middle of a singly linked list, given the node as input.
 *
 * Since you have no access to prior nodes, you can't change pointers to the current node,
 * so the only way to do this is by moving element values between nodes.
 *
 * You also can't do it if this is the last node.
 */

#include <vector>
#include <assert.h>

#include "list.h"

template<typename T>
void
delete_node(Node<T>* to_delete)
{
    if (to_delete == NULL) {
        return;
    }

    while(to_delete->next != NULL) {
        to_delete->elem = to_delete->next->elem;

        // If this node was second-last, it's now the last one.
        if (to_delete->next->next == NULL) {
            to_delete->next = NULL;
        } else {
        // General case: just move on.
            to_delete = to_delete->next;
        }
    }
}


int main()
{
    using namespace std;

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    Node<int>* list = make_list(vec.begin(), vec.end());

    delete_node(list->next);

    assert( list->elem == 1 );
    assert( list->next->elem == 3 );
    assert( list->next->next == NULL );
}
