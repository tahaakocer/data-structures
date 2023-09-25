#include <iostream>
#include <cstdlib>

using namespace std;

struct Person {
    int id;
    int processing_time;
    int waiting_time;
};

class Queue {
private:
    Person *people;
    int front;
    int rear;
    int capacity;
    int size;

public:
    Queue(int queueCapacity) {
        capacity = queueCapacity;
        people = new Person[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    void enqueue(int id) {
        if (size < capacity) {
            rear = (rear + 1) % capacity;
            people[rear].id = id;
            people[rear].processing_time = rand() % 271 + 30;
            people[rear].waiting_time = 0;

            size++;
        } else {
            cout << "Queue is full" << endl;
        }
    }

    void dequeue() {
        if (!is_empty()) {
            int waiting_time = 0;
            for (int i = front; i != (rear + 1) % capacity; i = (i + 1) % capacity) {
                waiting_time += people[i].processing_time;
            }

            cout << "Kuyruktan ayrilan kisi: id: " << people[front].id
                 << ", islem suresi: " << people[front].processing_time
                 << ", bekleme suresi: " << waiting_time << endl;

            front = (front + 1) % capacity;
            size--;
        } else {
            cout << "Queue is empty" << endl;
        }
    }

    bool is_empty() {
        return size == 0;
    }

    ~Queue() {
        delete[] people;
    }
};

int main() {
    int n;
    cout << "Kisi sayisi: ";
    cin >> n;
    Queue q(n); // Maksimum kuyruk kapasitesini kişi sayısı ile başlat

    for (int i = 0; i < n; i++) {
        q.enqueue(i);
    }

    for (int i = 0; i < n; i++) {
        q.dequeue();
    }

    return 0;
}
