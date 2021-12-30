#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif
#include<iostream>
using namespace std;

template<class T> class Queue
{
public:
    int front;
    int rear;
    int size; //Free to define (recommand 100 or 200)
    T* val;

    Queue() {
        size = 200;//initialization
        val = new T[size];
        front = rear =0;//initialization
    }
    ~Queue()
    {
        delete[] val;
    }

    void push(T value) {
        // input data
        if (!isFull()) {
            val[rear] = value;
            rear = (rear + 1) % size;
        }
        else { cout << "You need to increase the size of the queue." << endl; }
    }

    void pop() {
        //Change Front
        if (!empty()) { front = (front + 1) % size; }
        else { cout << "There is nothing in the queue." << endl; }
    }

    bool empty() {
        //Check its empty or not
        if (front!=rear) { return false; }
        else { return true; }
    }

    bool isFull() {
        //Check queue is full or not
        if ((rear + 1) % size == front) { return true; }
        else { return false; }
    }
};


#endif
