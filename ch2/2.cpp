
#include "list.h"

#include <assert.h>
#include <vector>

/*
 * Return the nth-to-last element of a singly linked list.
 *
 * Clarifications:
 * - If fewer than n elements, return the head.
 *
 * - nth-last interpreted as "n spaces from last",
 *   so n==0 -> last element,
 *      n==1 -> second last,
 *      etc.
 */
Node<int>*
nth_last(Node<int>* head, size_t n)
{
    if (head == NULL) {
        return NULL;
    }

    Node<int> *front = head,
              *rear = head;
    // num_walked is number of steps front has advanced beyond rear.
    size_t num_walked = 0;

    while (front->next != NULL) {
        front = front->next;

        if (num_walked < n) {
            ++num_walked;
        } else {
            rear = rear->next;
        }
    }

    return rear;
}


int main()
{
    using namespace std;

    vector<int> vec;
    vec.push_back(1);
    assert( nth_last(make_list(vec.begin(), vec.end()), 0)->elem == 1);
    assert( nth_last(make_list(vec.begin(), vec.end()), 1)->elem == 1);
    assert( nth_last(make_list(vec.begin(), vec.end()), 100)->elem == 1);

    vec.push_back(2);
    vec.push_back(3);
    assert( nth_last(make_list(vec.begin(), vec.end()), 0)->elem == 3);
    assert( nth_last(make_list(vec.begin(), vec.end()), 1)->elem == 2);
    assert( nth_last(make_list(vec.begin(), vec.end()), 2)->elem == 1);
    assert( nth_last(make_list(vec.begin(), vec.end()), 2)->elem == 1);
    assert( nth_last(make_list(vec.begin(), vec.end()), 3)->elem == 1);
}
