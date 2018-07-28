#ifndef SEARCHINGALGO.H
#define SEARCHINGALGO.H

#include <list>
#include <iostream>
#include <cmath>
using namespace std;

template <class Type>
class SearchingAlgo {
    public:
        // This method performs linear search on the item passed to the function.
        // arrList: array used for the searching of the item.
        // num: number of elements in arrList.
        // Worst case complexity: O(n) where n is the number of elements in arrList.
        bool linearSearch(Type arrList[], int num, Type item);

        // Time Complexity: O(log n)
        bool binarySearch(Type arrListSorted[], int num, Type item);

        // Perform jump search whereby the comparison is made by jumping
        // ahead by a fixed number of steps through the array.
        // The array needs to be sorted.
        // Time Complexity: O(sqrt(n)) where n is the number of elements in arrListSorted.
        bool jumpSearch(Type arrListSorted[], int num, Type item);

        // Time complexity: O(log log n)
        bool interpolationSearch(Type arrListSorted[], int num, Type item);

        //
        bool exponentialSearch(Type arrList[], int num, Type item);
        bool sublistSearch(list<Type> largeList, list<Type> smallList);
        bool fibonacciSearch(Type arrList[], int num, Type item);
        bool recursiveLinearSearch(Type arrList[], int num, Type item);
        bool recursiveSublistSearch(list<Type> largeList, list<Type> smallList);

    private:
        bool recursiveLinearSearch(Type arrList[], int startIn, int endIn, Type item);
        bool recursiveSublistSearch(list<Type> largeList, const_iterator largeIt, list<Type> smallList, const_iterator smallIt);

};

template <class Type>
bool SearchingAlgo<Type>::linearSearch(Type arrList[], int num, Type item){
    for(int i = 0; i < num; i++){
        if(arrList[i] == item)
            return true;
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::binarySearch(Type arrListSorted[], int num, Type item){
    if(num > 0){
        int begIndex = 0, lastIndex = num - 1;
        while(begIndex <= lastIndex){
            int middleIndex = (begIndex + lastIndex) / 2;
            if(arrListSorted[middleIndex] > item)
                lastIndex = middleIndex - 1;
            else if(arrListSorted[middleIndex] < item)
                begIndex = middleIndex + 1;
            else
                return true;
        }
        return false;
    }
}

template <class Type>
bool SearchingAlgo<Type>::jumpSearch(Type arrListSorted[], int num, Type item){
    if(num > 0){
        int prev = 0;
        int step = sqrt(num);
        int jumpLoc = step;

        while(arrListSorted[min(jumpLoc, num) - 1] < item){
            if(jumpLoc >= num)
                return false;

            prev = jumpLoc;
            jumpLoc += step;
        }

        if(jumpLoc > num)
            jumpLoc = num;

        while(prev <= jumpLoc - 1){
            if(arrListSorted[prev] == item)
                return true;
            prev++;
        }
        return false;
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::interpolationSearch(Type arrListSorted[], int num, Type item){
    int begIndex = 0;
    int lastIndex = num - 1;
    int pos = begIndex
            + (double)(item - arrListSorted[begIndex])
            / (arrListSorted[lastIndex] - arrListSorted[begIndex])
            * (lastIndex - begIndex);

    while(begIndex <= pos && pos <= lastIndex){
        if(arrListSorted[pos] < item)
            begIndex = pos + 1;
        else if(arrListSorted[pos] > item)
            lastIndex = pos - 1;
        else
            return true;

        pos = begIndex
            + static_cast<double>(item - arrListSorted[begIndex])
            / (arrListSorted[lastIndex] - arrListSorted[begIndex])
            * (lastIndex - begIndex);
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::exponentialSearch(Type arrList[], int num, Type item){
    if(num > 0){
        int index = 1;
        while(index < num && arrList[index] < item)
            index *= 2;

        int prev = index / 2;
        if(index >= num)
            index = num - 1;

        int middle;
        while(prev <= index){
            middle = (prev + index) / 2;
            if(arrList[middle] < item)
                prev = middle + 1;
            else if(arrList[middle] > item)
                index = middle - 1;
            else
                return true;
        }

        return false;
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::sublistSearch(list<Type> largeList, list<Type> smallList){
    if(largeList.empty() && !smallList.empty())
        return true;
    else if(largeList.size() > smallList.size()) {
        const_iterator largeIt = largeList.begin();
        const_iterator smallIt = smallList.begin();
        const_iterator returnLargeList = largeIt;

        do{
            if(*largeIt == *smallIt){
                smallIt++;
                largeIt++;
            }
            else{
                smallIt = smallList.begin();
                largeIt = ++returnLargeList;
            }
        } while(largeIt != largeList.end() && smallIt != smallList.end());

        if(smallIt == smallList.end())
            return true;
        else
            return false;
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::fibonacciSearch(Type arrList[], int num, Type item){
    int fibN_1 = 1;
    int fibN_2 = 0;
    int fib = fibN_1 + fibN_2;

    while(fib < num){
        fibN_2 = fibN_1;
        fibN_1 = fib;
        fib = fibN_1 + fibN_2;
    }

    int offset = -1;

    while(fib > 1){
        int index = min(fibN_2 + offset, num - 1);

        if(arrList[index] < item){
            fib = fibN_1;
            fibN_1 = fibN_2;
            fibN_2 = fib - fibN_1;
            offset = index;
        }

        else if(arrList[index] > item){
            fib = fibN_2;
            fibN_1 = fibN_1 - fibN_2;
            fibN_2 = fib - fibN_1;
        }

        else
            return true;
    }

    if(fib && arrList[offset+1] == item)
        return true;
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::recursiveLinearSearch(Type arrList[], int num, Type item){
    return recursiveLinearSearch(arrList, 0, num - 1, item);
}

template <class Type>
bool SearchingAlgo<Type>::recursiveLinearSearch(Type arrList[], int startIn, int endIn, Type item){
    if(startIn <= endIn)
        if(arrList[startIn] == item)
            return true;
        else
            return recursiveLinearSearch(arrList, startIn + 1, endIn, item);

    return false;
}

template <class Type>
bool SearchingAlgo<Type>::recursiveSublistSearch(list<Type> largeList, list<Type> smallList){
    recursiveSublistSearch(largeList, largeList.begin(), largeList.begin(), smallList, smallList.begin());
}
template <class Type>
bool SearchingAlgo<Type>::recursiveSublistSearch(list<Type> largeList, const_iterator largeIt, const_iterator startLoc,
                                                 list<Type> smallList, const_iterator smallIt){
    if(smallIt == smallList.end())
        return true;
    else if(largeIt == largeList.end())
        return false;
    else {
        if(*largeIt == *smallIt)
            recursiveSublistSearch(largeList, ++largeIt, startLoc, smallList, ++smallIt);
        else{
            startLoc++;
            recursiveSublistSearch(largeList, startLoc, startLoc, smallList, smallList.begin());
        }
    }
}

#endif // SEARCHINGALGO.H


