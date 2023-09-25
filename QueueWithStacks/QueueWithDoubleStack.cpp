#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
    int id;
    int processing_time;
    int waiting_time; // yeni eklenen değişken
    struct Node *next;
};

class Stack
{
private:
    

public:
    Node *top;
    Stack()
    {
        top = NULL;
    }
    void push(int val)
    {
        Node *new_node = new Node;
        new_node->id = val;
        new_node->processing_time = rand() % 271 + 30;
        new_node->waiting_time = 0; // başlangıçta waiting time sıfır olarak ayarlanır
        new_node->next = top;
        top = new_node;
    }
    Node *pop()
    {
        if (top == NULL)
        {
            cout << "Stack is empty" << endl;
            return NULL;
        }
        Node *temp = top;
        top = top->next;
        return temp;
    }
    int peek()
    {
        if (top == NULL)
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return top->id;
    }
    bool is_empty()
    {
        return top == NULL;
    }
};

class Queue
{
private:
    Stack s1, s2;

public:
    void enqueue(int x)
    {
        while (!s1.is_empty())
        {
            s2.push(s1.peek());
            s1.pop();
        }
        s1.push(x);
        while (!s2.is_empty())
        {
            s1.push(s2.peek());
            s2.pop();
        }
    }
    void dequeue()
{
    if (s1.is_empty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    // Bekleme süresi hesaplama
    int waiting_time = 0;
    Node *temp = s1.top;
    while (temp != NULL)
    {
        waiting_time += temp->processing_time;
        temp = temp->next;
    }

    Node *dequeued_node = s1.pop();
    dequeued_node->waiting_time = waiting_time;

    cout << "Kuyruktan ayrilan kisi: id: " << dequeued_node->id
         << ", islem suresi: " << dequeued_node->processing_time
         << ", bekleme suresi: " << dequeued_node->waiting_time << endl;
    delete dequeued_node;
}
    
};

int main()
{
    int n;
    cout << "Kisi sayisi: ";
    cin >> n;
    Queue q;
    for (int i = 0; i < n; i++)
    {
        q.enqueue(i);
    }

    for (int i = 0; i < n; i++)
    {
        q.dequeue();
    }
    system("pause");
    return 0;
}
