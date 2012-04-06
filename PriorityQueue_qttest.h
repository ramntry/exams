#pragma once
#include <QtTest/QtTest>
#include "PriorityQueue.h"

class PriorityQueueTest : public QObject
{
    Q_OBJECT

private slots:
    void init()
    {
        pq = new PriorityQueue<int>;
    }

    void testAddItemInEmptyQueue()
    {
        pq->enqueue(100, 1);
        pq->enqueue(200, 2);
    }

    void testDequeueFromEmptyQueue()
    {
        try
        {
            pq->dequeue();
            QFAIL("DequeueFromEmptyPriorityQueueException wasn't thrown");
        }
        catch (DequeueFromEmptyPriorityQueueException const& e) {}
    }

    void testDequeueFromQueueWithOneItem()
    {
        pq->enqueue(100, 1);
        QCOMPARE(100, pq->dequeue());
    }

    void testDequeueFromBigQueue()
    {
        int items[]  = { 10, 20, 50, 40, 30, 60, 70 };
        for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
            pq->enqueue(items[i], items[i] / 10);

        bool ok = true;
        int right[]  = { 70, 60, 50, 40, 30, 20, 10 };
            for (size_t i = 0; i < sizeof(items)/sizeof(int); ++i)
                ok = ok && (pq->dequeue() == right[i]);

        QVERIFY(ok);
    }

    void cleanup()
    {
        delete pq;
    }

private:
    PriorityQueue<int> *pq;
};

QTEST_APPLESS_MAIN(PriorityQueueTest)
