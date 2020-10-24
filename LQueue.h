#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *next;
}*front=NULL,*rear=NULL;

class Queue {

    public:
        void enqueue(int x);
        int dequeue();
        void Display();
        bool isEmpty();
}qe;

void Queue::enqueue(int x) {

    Node *t = new Node; 
    if(t==NULL) cout<<"Queue full"<<endl;
    else {
        t->data=x;
        t->next=NULL;
        if(front==NULL)
            front=rear=t;
        else {
            rear->next=t;
            rear=t;
        }
    }
}

int Queue::dequeue() {

    int x=-1;
    Node *t;

    if(front==NULL) cout<<"Queue Empty";
    else {
        x=front->data;
        t=front;
        front=front->next;
        delete t;
    }
    return x;
}

bool Queue::isEmpty() {
    return front == NULL;
}

void Queue::Display() {
    Node *p=front;
    while(p) {
        cout<<p->data<<endl;
        p=p->next;
    }
}