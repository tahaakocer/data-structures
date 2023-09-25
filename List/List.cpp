#include <iostream>
#include <stdlib.h>
#include <string.h>
#define NUM_SIZE = 15;
#define NAME_SIZE = 30;

using namespace std;

struct Node
{
    int deger;
    Node *next;
};

struct PList
{
    Node *head;
    int numOfNodes;
    void create();
    void addToEnd(Node *);
    void addToFront(Node *);
    void addToMid(Node *);
    void print();
};
void PList::create()
{
    head = NULL;
    numOfNodes = 0;
}

void PList::addToFront(Node *n)
{
    if (head == NULL)
    {
        head = n;
    }
    else
    {
        n->next = head;
        head = n;
    }
}

void PList::addToEnd(Node *n)
{
    if (head == NULL)
    {
        head = n;
        return;
    }
    Node *scan;
    scan = head;
    while (scan->next)
    {
        scan = scan->next;
    }
    scan->next = n;
}
void PList::addToMid(Node *n)
{
    if (head == NULL)
    {
        head = n;
        return;
    }
    numOfNodes = 0;
    Node *scan;
    scan = head;
    while (scan)
    {
        numOfNodes++;
        scan = scan->next;
    }
    scan = head;
    for (int i = 0; i < numOfNodes / 2 - 1; i++)
    {
        scan = scan->next;
    }
    n->next = scan->next;
    scan->next = n;
}
void PList::print()
{
    Node *scan;
    scan = head;
    if (!scan)
    {
        cout << "Liste bos!!!" << endl;
        return;
    }
    while (scan)
    {
        cout << scan->deger << " ";
        scan = scan->next;
    }
    cout << endl;
}
int main()
{
    PList *l = new PList();
    l->create();
    l->print();
    
    Node *n = new Node();
    n->deger = 1;
    l->addToFront(n);
    l->print();

    n = new Node();
    n->deger = 2;
    l->addToEnd(n);
    l->print();

    n = new Node();
    n->deger = 3;
    l->addToMid(n);
    l->print();

    n = new Node();
    n->deger = 4;
    l->addToFront(n);
    l->print();
    
    return 0;
}
