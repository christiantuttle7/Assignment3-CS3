#pragma once

template <class T1>
class Node
{
    private:
    T1 _data;
    Node<T1>* nextNode;

    public:
    Node();
    void setData(T1);
    
    void setNext(Node<T1>*);
    T1 getData();
    Node<T1>* getPrev();
    Node<T1>* getNext();
};

template <class T1>
Node<T1>::Node()
{
    nextNode = nullptr;
}

template <class T1>
void Node<T1>::setData(T1 data)
{
    _data = data;
}



template <class T1>
void Node<T1>::setNext(Node<T1>* next)
{
    nextNode = next;
}

template <class T1>
T1 Node<T1>::getData()
{
    return _data;
}



template <class T1>
Node<T1>* Node<T1>::getNext()
{
    return nextNode;
}