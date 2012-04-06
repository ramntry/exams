#pragma once
#include <stdexcept>
#include <utility>

class DequeueFromEmptyPriorityQueueException : public std::underflow_error
{
public:
    DequeueFromEmptyPriorityQueueException(std::string const& what_arg)
        : std::underflow_error(what_arg)
    {}
};

template <typename T>
class PriorityQueue
{
    static const size_t defaultCapacity = 10;

    class Node : public std::pair<int, T>
    {
    public:
        Node() {}

        Node(int priority, T const& item)
            : std::pair<int, T>(priority, item)
        {}

    friend bool operator >(Node const& a, Node const& b)
    { return a.first > b.first; }

    };

public:
    PriorityQueue(size_t initCapacity = defaultCapacity);
    ~PriorityQueue();

    void enqueue(T const& item, int priority);
    T dequeue() throw (DequeueFromEmptyPriorityQueueException);

private:
    void siftDownHeadItem();
    void siftUpNextItem();

    size_t capacity;
    size_t size;

    Node *heap;
};

template <typename T>
PriorityQueue<T>::PriorityQueue(size_t initCapacity)
    : capacity(initCapacity)
    , size(0)
    , heap(new Node[capacity])
{}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    delete[] heap;
}
template <typename T>
void PriorityQueue<T>::siftDownHeadItem()
{
    size_t pos = 0;
    size_t greatest = pos;
    for (;;)
    {
        size_t left = (pos + 1) * 2 - 1;
        size_t right = (pos + 1) * 2;

        if (left < size)
        {
            if (heap[left] > heap[greatest])
                greatest = left;

            if (right < size && heap[right] > heap[greatest])
                greatest = right;
        }
        if (pos != greatest)
        {
            std::swap(heap[pos], heap[greatest]);
            pos = greatest;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::siftUpNextItem()
{
    size_t pos = size;
    while (pos > 0)
    {
        size_t parent = (pos + 1) / 2 - 1;
        if (heap[pos] > heap[parent])
        {
            std::swap(heap[pos], heap[parent]);
            pos = parent;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::enqueue(T const& item, int priority)
{
    if (size == capacity)
    {
        Node *tmp = new Node[capacity *= 2];

        for (size_t i = 0; i < size; ++i)
            tmp[i] = heap[i];

        delete[] heap;
        heap = tmp;
    }

    heap[size] = Node(priority, item);
    siftUpNextItem();
    size++;
}

template <typename T>
T PriorityQueue<T>::dequeue() throw (DequeueFromEmptyPriorityQueueException)
{
    if (size == 0)
        throw DequeueFromEmptyPriorityQueueException("Unable to get an item from an empty queue");

    std::swap(heap[0], heap[--size]);
    siftDownHeadItem();
    return heap[size].second;
}
