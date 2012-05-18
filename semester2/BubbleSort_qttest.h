#pragma once
#include <QtTest/QtTest>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "BubbleSort.h"

class BubbleSortTest : public QObject
{
    Q_OBJECT

private slots:
    void simpleArrayTest()
    {
        int task[] = { 1, 6, 3, 5, 3, 2, 4, 6, 3 };
        size_t size = sizeof(task)/sizeof(int);

        bubbleSort<int>(task, task + size, StandartComparator<int>());

        for (size_t i = 0; i < size - 1;)
            QVERIFY(task[i] <= task[++i]);
    }

    void vectorTest()
    {
        int task[] = { 1, 6, 3, 5, 3, 2, 4, 6, 3 };
        size_t size = sizeof(task)/sizeof(int);
        std::vector<int> v(task, task + size);

        bubbleSort<int>(v.begin(), v.end(), StandartComparator<int>());

        for (size_t i = 0; i < size - 1;)
            QVERIFY(v[i] <= v[++i]);
    }

    void comparatorAndListTest()
    {
        IgnoreCaseStringComparator comp;

        std::list<std::string> list;
        list.push_back("MANGO");
        list.push_back("mango");
        list.push_back("Mango");

        list.push_back("apple");
        list.push_back("Apple");
        list.push_back("APPLE");

        bubbleSort<std::string>(list.begin(), list.end(), comp);

        std::ostringstream os;
        std::list<std::string>::iterator it = list.begin();
        for (; it != list.end(); ++it)
            os << *it << ' ';

        QCOMPARE(os.str(), std::string("apple Apple APPLE MANGO mango Mango "));
    }
};
