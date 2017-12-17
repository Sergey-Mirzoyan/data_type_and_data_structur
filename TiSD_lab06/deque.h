//
// Created by serych on 05.12.16.
//

#ifndef LABA6_TISD_DEQUE_H
#define LABA6_TISD_DEQUE_H

#include <assert.h>
#define DEFAULT_SIZE 4

using namespace std;

template <class T>
class Deque {
public:
    Deque(int size);
    Deque();
    ~Deque();

    void PushFront(T data);
    void PushBack(T data);
    T PopBack();
    T PopFront();
    T GetBack();
    T GetFront();
    bool IsEmpty() const;

    void print(bool debug = false) const;

private:
    T* buffer = NULL;
    int bufferSize;
    int minBufferSize;
    int head;
    int tail;
    bool empty;
    void IncreaseBuffer();
    void DecreaseBuffer();
};

template <typename T>
Deque<T>::Deque(int size) : bufferSize(size), minBufferSize(size), head(-1), tail(0), empty(true)
{
    assert(size > 1);
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::Deque() : bufferSize(DEFAULT_SIZE), minBufferSize(DEFAULT_SIZE), head(-1
), tail(0), empty(true)
{
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::~Deque()
{
    delete[](buffer);
}

template <typename T>
void Deque<T>::IncreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize * 2)];
    assert(tmpBuffer);

    tmpBuffer[0] = buffer[head];
    for (int i = bufferSize + 1; i < bufferSize * 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i - 1 - bufferSize) % bufferSize];
    }
    head = 0;
    tail = bufferSize + 1;
    bufferSize *= 2;

    delete [](buffer);
    buffer = tmpBuffer;
}

template <typename T>
void Deque<T>::DecreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize / 2)];
    assert(tmpBuffer);
    assert(bufferSize >= minBufferSize);

    tmpBuffer[0] = buffer[head];
    for (int i = 1; i < bufferSize / 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i - 1) % bufferSize];
    }

    head = 0;
    tail = 1;
    bufferSize /= 2;

    delete [](buffer);
    buffer = tmpBuffer;
}

template <typename T>
void Deque<T>::PushFront(T data)
{
    if (IsEmpty()) {
        buffer[0] = data;
        head = 0;
        tail = 0;
        empty = false;
    }
    else
    {
        head = (head + 1) % bufferSize;
        if (head == tail) {
            head--;
            if (head < 0)
                head = bufferSize - 1;
            IncreaseBuffer();
            head++;
        }
        buffer[head] = data;
    }
}


template <typename T>
void Deque<T>::PushBack(T data) {
    if (IsEmpty()) {
        buffer[bufferSize - 1] = data;
        tail = bufferSize - 1;
        head = bufferSize - 1;
        empty = false;
    }
    else
    {
        tail = (tail - 1);
        if (tail < 0)
            tail = bufferSize - 1;
        if (head == tail) {
            tail = (tail + 1) % bufferSize;
            IncreaseBuffer();
            tail--;
        }
        buffer[tail] = data;
    }

}


template <typename T>
T Deque<T>::PopBack() {
    if (IsEmpty())
        throw "Cannot pop from empty Deque";
    if (tail == head)
        empty = true;
    T data = buffer[tail];
    tail = (tail + 1) % bufferSize;
    int rasst = (tail > head) ? head + bufferSize - tail : head - tail;
    if (rasst < bufferSize / 2  && bufferSize > minBufferSize)
    {
        DecreaseBuffer();
    }
    return data;
}


template <typename T>
T Deque<T>::PopFront() {
    if (IsEmpty())
        throw "Cannot pop from empty Deque";
    if (tail == head)
        empty = true;
    T data = buffer[head];
    head = (head - 1);
    if (head < 0)
        head = bufferSize - 1;

    int rasst = (tail > head) ? head + bufferSize - tail : head - tail;
    if (rasst < bufferSize / 2  && bufferSize > minBufferSize)
    {
        DecreaseBuffer();
    }
    return data;
}


template <typename T>
bool Deque<T>::IsEmpty() const
{
    return empty;
}

template <typename T>
void Deque<T>::print(bool debug) const {
    if (debug)
        std::cout << "Head: " << head << "; Tail: " << tail << std::endl;
    std::cout << "|";
    for (int i = 0; i < bufferSize; i++)
    {
        std::cout << " " << buffer[i] << " |";
    }
}

template <typename T>
T Deque<T>::GetFront() {
    if (IsEmpty())
        throw "Cannot get from empty Deque";
    return buffer[head];
}
template <typename T>
T Deque<T>::GetBack() {
    if (IsEmpty())
        throw "Cannot get from empty Deque";
    return buffer[tail];
}


#endif //LABA6_TISD_DEQUE_H
