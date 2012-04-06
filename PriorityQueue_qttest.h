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
        int rights[] = { 70, 60, 50, 40, 30, 20, 10 };

        multipleAdd(items, sizeof(items)/sizeof(int));
        QVERIFY(multipleCheck(rights, sizeof(rights)/sizeof(int)));
    }

    void testReallocPriorityQueue()
    {
        int items[]  = { 500, 400, 300, 200, 100, 10, 20, 50, 40, 30, 60, 70 };
        int rights[] = { 500, 400, 300, 200, 100, 70, 60, 50, 40, 30, 20, 10 };

        multipleAdd(items, sizeof(items)/sizeof(int));
        QVERIFY(multipleCheck(rights, sizeof(rights)/sizeof(int)));
    }

    void cleanup()
    {
        delete pq;
    }

private:
    PriorityQueue<int> *pq;

    void multipleAdd(int *items, size_t num)
    {
        for (size_t i = 0; i < num; ++i)
            pq->enqueue(items[i], items[i] / 10);
    }

    bool multipleCheck(int *rights, size_t num)
    {
        bool ok = true;

        for (size_t i = 0; i < num; ++i)
            ok = ok && (pq->dequeue() == rights[i]);

        return ok;
    }
};

QTEST_APPLESS_MAIN(PriorityQueueTest)

