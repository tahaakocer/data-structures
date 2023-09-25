#include <iostream>
using namespace std;
typedef int queueDataType;

struct Node
{
    queueDataType data;
    Node* next;   
};

struct Queue
{
    Node *head; // baş düğüm
    Node *last; // son düğüm
    void create();
    void close();
    void push(queueDataType);
    queueDataType pop();
    void print();
    bool isEmpty();
};
void Queue::create() {
    head = NULL;
    last = NULL;
}
void Queue::close() {
    Node *p;
    /*baş düğüm NULL değer döndürene kadar birbirine bağlanmış düğümleri
    sırayla "delete" komutuyla bellekten temizliyoruz.*/
    while(head){
        p = head;
        head = head->next;
        delete p;
    }
}
void Queue::push(queueDataType newData) {
    Node *newNode = new Node; //yeni düğüm
    newNode->data = newData;
    newNode->next = NULL;
    //Kuyruğa ilk düğüm ekleniyor ise:
    if(head == NULL) {
        head = newNode;
        last = head;
    } 
    else {
        //son düğümün next'ine yeni düğüm ekleniyor.
        last->next = newNode;
        //son düğüm değişkeni yeni düğüm ile güncelleniyor.
        last = newNode;
        //böylece iki düğümü birbirine bağlamış olduk.
    }
}
queueDataType Queue::pop() {
    Node *topNode; //üst düğüm
    queueDataType temp; 
    topNode = head;
    //baş düğümü sileceğimiz için bir sonraki düğümü baş olarak güncelliyoruz.
    head = head->next;
    //fonksiyon silinen kuyruğun değerini döndürecek.
    temp = topNode->data;
    delete topNode;
    return temp;

}
bool Queue::isEmpty() {
    return (head == NULL) ? true : false;
}
void Queue::print() {
    Node *tara; //taramak için kullanılacak geçiçi değişken.
    tara = head;
    while(tara){
        cout << tara->data << endl;
        tara = tara->next;
    }
    cout << endl;
}
int main(int argc, char const *argv[])
{
    // Kuyruk veri yapısı oluştur.
    Queue *queue = new Queue();

    // ekle , çıkar ve yazdır.
    queue->push(1);
    queue->push(4);
    queue->push(3);
    queue->print();
    queue->pop();
    queue->print();
    return 0;
}
