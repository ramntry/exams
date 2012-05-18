#pragma once
#include "Comparator.h"

namespace sorters
{
template <typename T>
inline void swap(T &a, T &b)
{
    T t(a);
    a = b;
    b = t;
}
}

template <typename T, typename I, typename C>
void bubbleSort(I beginIt, I endIterator, C comp)
{
    for (I i = --endIterator; i != beginIt; --i)
        for (I j = beginIt; j != i;)
        {
            T &curr = *j;
            T &next = *(++j);

            if (comp(curr, next) > 0)
                sorters::swap(curr, next);
        }
}

int bubbleSortTestExec(int argc, char **argv);
