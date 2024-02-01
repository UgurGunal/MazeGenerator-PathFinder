#pragma once
#include <iostream>

template <class Object>
class Stack
{
public:
    Stack()
    {
        topOfStack = NULL;
    }
    Stack(const Stack& rhs)
    {
        topOfStack = NULL;
        *this = rhs; // deep copy 
    }
    ~Stack()
    {
        makeEmpty();
    }

    bool isEmpty() const
    {
        return topOfStack == NULL;
    }
    bool isFull() const
    {
        return false;
    }
    void makeEmpty()
    {
        while (!isEmpty())
            pop();
    }

    void pop()
    {
        if (!isEmpty())
        {
            ListNode* oldTop = topOfStack;
            topOfStack = topOfStack->next;
            delete oldTop;
        }
        else 
        {
            throw UNDERFLOW;
        }
    }
    void push(const Object& x)
    {
        topOfStack = new ListNode(x, topOfStack);
    }
    Object topAndPop()
    {
        Object topItem = top();
        pop();
        return topItem;
    }
    const Object& top() const
    {
        if (!isEmpty())
        {
            return topOfStack->element;
        }
    }

    const Stack& operator=(const Stack& rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            if (rhs.isEmpty()) {
                return *this;
            }
            ListNode* rptr = rhs.topOfStack;
            ListNode* ptr = new ListNode(rptr->element);
            topOfStack = ptr;
            for (rptr = rptr->next; rptr != NULL; rptr = rptr->next) {
                ptr = ptr->next = new ListNode(rptr->element);
            }
        }
        return *this;
    }

private:
    struct ListNode
    {
        Object   element;
        ListNode* next;

        ListNode(const Object& theElement, ListNode* n = NULL)
            : element(theElement), next(n) { }
    };

    ListNode* topOfStack;  // list itself is the stack
};
