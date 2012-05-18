#include "BubbleSort_qttest.h"

int bubbleSortTestExec(int argc, char **argv)
{
    BubbleSortTest bst;
    return QTest::qExec(&bst, argc, argv);
}
