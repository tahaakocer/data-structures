#include <iostream>
#include <stdlib.h>
#define STACK_H
#define STACK_SIZE 5

using namespace std;
typedef char stackDataType;

struct Node
{
    stackDataType data;
    Node *next;
};
struct Stack
{
    Node *head;
    void create();
    void close();
    void push(stackDataType);
    stackDataType pop();
    void print();
    bool isEmpty();
};
void Stack::create()
{
    head == NULL;
}
void Stack::close()
{
    Node *p;
    while (head)
    {
        p = head;
        head = head->next;
        delete p;
    }
}
void Stack::push(stackDataType n)
{
    Node *newNode = new Node();
    newNode->data = n;
    newNode->next = head;
    head = newNode;
}
stackDataType Stack::pop()
{
    Node *topNode;
    stackDataType temp;
    topNode = head;
    head = head->next;
    temp = topNode->data;
    delete topNode;
    return temp;
}
bool Stack::isEmpty()
{
    return (head == NULL) ? true : false;
}

void Stack::print()
{
    Node *tara;
    tara = head;
    while(tara)
    {
        cout << tara->data << endl;
        tara = tara->next;
    }
}
int main()
{
    Stack *stack = new Stack();
    stack->create();
    stack->push('a');
    stack->push('b');
    stack->push('c');
    stack->pop();
    stack->print();

    return 0;
}
