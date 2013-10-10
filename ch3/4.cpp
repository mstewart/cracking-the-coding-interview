#include <stack>
#include <exception>
#include <assert.h>
#include <iostream>

using namespace std;

class HanoiSpindle
    : public stack<int>
{
    public:
    void push(int x) {
        if (! empty() && top() < x) {
            throw exception();
        }
        stack::push(x);
    }
};


/**
 * Move a stack of depth `stack_depth` from source to dest,
 * with a third temporary spindle available.
 */
void
hanoi_move_stack(HanoiSpindle& source,
        size_t stack_depth,
        HanoiSpindle& dest,
        HanoiSpindle& tmp)
{
    if (stack_depth == 0) {
        return;
    }

    // move stack of length (stack_depth - 1) from source -> tmp,
    hanoi_move_stack(source,
            stack_depth - 1,
            tmp, dest);

    // move bottom element from source to dest
    dest.push(source.top());
    source.pop();

    // move stack of length (stack_depth - 1) from tmp -> dest
    hanoi_move_stack(tmp,
            stack_depth - 1,
            dest,
            source);
}



int main()
{
    HanoiSpindle spindle[3];

    for (int i = 10; i > 0; --i) {
        spindle[0].push(i);
    }

    hanoi_move_stack(spindle[0],
        10,
        spindle[1],
        spindle[2]);

    assert( spindle[0].empty() );
    assert( spindle[2].empty() );
    assert( spindle[1].size() == 10 );
}
