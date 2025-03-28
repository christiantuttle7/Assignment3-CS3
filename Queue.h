#ifndef QUEUE_H
#define QUEUE_H

#include "ResizingArray.h"

template <typename T>
class Queue {
private:
    ResizingArray<T> data;

public:
    void Enqueue(T value) {
        // uses ResizingArray's Push
        data.Push(value);
    }

    T Dequeue() {
        if (IsEmpty()) {
            throw std::out_of_range("Queue underflow");
        }

        T frontElement = data[0];

        // shifts all elements one position to the left
        for (int i = 1; i < data.getSize(); i++) {
            data[i - 1] = data[i];
        }

        data.Pop();  // removes the duplicate at the end (due to the shift)
        return frontElement;
    }

    T Front() {
        if (IsEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        // returns the front of the queue
        return data[0];
    }

    bool IsEmpty() {
        return data.getSize() == 0;
    }
};

#endif