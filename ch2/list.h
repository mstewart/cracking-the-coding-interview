/*
 * Extremely simple linked list template class.
 */

#ifndef _CRACKING_LIST_H_
#define _CRACKING_LIST_H_

#include <cstddef>

template<typename T>
struct Node
{
    const T elem;
    Node* next;

    Node(const T& elem)
        : elem(elem)
        , next(NULL)
    {}
};


template<typename iter_t>
Node<typename iter_t::value_type>*
make_list(iter_t start, iter_t end)
{
    typedef typename iter_t::value_type elem_t;

    Node<elem_t>*   head = NULL;
    Node<elem_t>*   tail = NULL;
    for (; start != end; ++start)
    {
        Node<elem_t>*   new_node = new Node<elem_t>(*start);

        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return head;
}

#endif
