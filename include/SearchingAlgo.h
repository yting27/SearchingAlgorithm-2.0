#ifndef SEARCHINGALGO_H
#define SEARCHINGALGO_H

#include <list>
#include <iostream>
#include <cmath>
using namespace std;

// Class Template
template <class Type>
class SearchingAlgo {
    public:
        // This method performs linear search on the item passed to the function.
        // arrList: array used for the searching of the item.
        // num: number of elements in arrList.
        // Worst case complexity: O(n) where n is the number of elements in arrList.
        bool linearSearch(Type arrList[], int num, const Type& item);

        // Perform binary search on sorted array.
        // Better performance than linearSearch.
        // Comparison is made between the middle element and the intended item.
        // return true if match is found and false if otherwise.
        // Time Complexity: O(log n)
        bool binarySearch(Type arrListSorted[], int num, const Type& item);

        // Perform jump search whereby the comparison is made by jumping
        // ahead by a fixed number of steps through the array.
        // The array needs to be sorted.
        // Time Complexity: O(sqrt(n)) where n is the number of elements in arrListSorted.
        bool jumpSearch(Type arrListSorted[], int num, const Type& item);

        // Interpolation search works well with sorted, uniformly distributed values of arrListSorted.
        // Improvement over binarySearch.
        // Time complexity: O(log log n)
        bool interpolationSearch(Type arrListSorted[], int num, const Type& item);

        // Exponential Search needs sorted array as well.
        // The comparison starts at (1*2)nd position element followed by (2*2)th element...
        // if mth element is greater than the item, the binary search is conducted on sub-array between m/2 and m.
        // Time complexity: O(log n)
        bool exponentialSearch(Type arrList[], int num, const Type& item);

        // Sublist search is used to compare 2 lists, namely list_1 (longer list) and list_2 (sublist).
        // If list_1 contains list_2, then true is returned; false otherwise.
        // Time complexity: O(m*n) where m is the number of nodes in second list and n in first list.
        bool sublistSearch(list<Type>& largeList, list<Type>& smallList);

        // Algorithm:
        // 1. Find the smallest fibonacci number (fib) greater than or equals to num.
        // (Find the corresponding fib_1 and fib_2) while fib > 1
        // 2. Comparing (fib_2)th element in arrList with item.
        //    i. if the element is greater than the item, move the three Fibonacci variables two Fibonacci down.
        //   ii. if the element is smaller than the item, move the three Fibonacci variables one Fibonacci down. Reset offset to index.
        //  iii. if match, return true.
        // Since there might be a single element remaining for comparison, check if fib is 1.
        // If Yes, compare x with that element. If match, return true.
        //Time Complexity: O(log n)
        bool fibonacciSearch(Type arrList[], int num, const Type& item);

        // Perform recursive linear search.
        bool recursiveLinearSearch(Type arrList[], int num, const Type& item);

        // Perform recursive sublist search.
        bool recursiveSublistSearch(list<Type>& largeList, list<Type>& smallList);

    private:
        bool recursiveLinearSearch(Type arrList[], int startIn, int endIn, const Type& item);
        bool recursiveSublistSearch(list<Type>& largeList, typename list<Type>::iterator largeIt, typename list<Type>::iterator startLoc, list<Type>& smallList,
                                    typename list<Type>::iterator smallIt);

};

template <class Type>
bool SearchingAlgo<Type>::linearSearch(Type arrList[], int num, const Type& item){
    // Linearly compare each element in arrList with item starting from the first item.
    for(int i = 0; i < num; i++){
        if(arrList[i] == item)
            return true;
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::binarySearch(Type arrListSorted[], int num, const Type& item){
    if(num > 0){
        int begIndex = 0, lastIndex = num - 1;
        while(begIndex <= lastIndex){
            // get index of middle element.
            int middleIndex = (begIndex + lastIndex) / 2;
            // if arrListSorted[middleIndex] is greater than item, the element to be search might be at the left subarray..
            if(arrListSorted[middleIndex] > item)
                lastIndex = middleIndex - 1;
            // if arrListSorted[middleIndex] is less than item, the element to be search might be at the right subarray..
            else if(arrListSorted[middleIndex] < item)
                begIndex = middleIndex + 1;
            // if match.
            else
                return true;
        }
        return false;
    }
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::jumpSearch(Type arrListSorted[], int num, const Type& item){
    if(num > 0){
        // To keep track of previous index after jumping.
        int prev = 0;
        // The number of steps taken for each jump.
        int step = sqrt(num);
        // Position of element to be compared after jump.
        int jumpLoc = step;

        // min() function is used to ensure that the index is in bound.
        while(arrListSorted[min(jumpLoc, num) - 1] < item){
            // If the statement is true, all the values in arrListSorted is smaller than the item.
            if(jumpLoc >= num)
                return false;

            prev = jumpLoc;
            jumpLoc += step;
        }

        if(jumpLoc > num)
            jumpLoc = num;

        // Linear search is performed within the range of ((n-1)*m)th and (n*m - 1)th.
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
bool SearchingAlgo<Type>::interpolationSearch(Type arrListSorted[], int num, const Type& item){
    int begIndex = 0;
    int lastIndex = num - 1;
    // Determine the position of element to be compared.
    int pos = begIndex
            + (double)(item - arrListSorted[begIndex])
            / (arrListSorted[lastIndex] - arrListSorted[begIndex])
            * (lastIndex - begIndex);

    // To ensure pos is within the range of arrListSorted.
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
bool SearchingAlgo<Type>::exponentialSearch(Type arrList[], int num, const Type& item){
    if(num > 0){
        int index = 1;
        // Determine the position of element where its value is greater or equal to item.
        while(arrList[min(index, num) - 1] < item){
            if(index > num)
                return false;
            index *= 2;
        }

        int prev = index / 2;
        if(index > num)
            index = num;
        int middle;

        // Binary search is performed between (index/2)th and (index-1)th element with item value.
        while(prev <= index - 1){
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
bool SearchingAlgo<Type>::sublistSearch(list<Type>& largeList, list<Type>& smallList){
    if(smallList.empty())
        return true;
    else if(largeList.size() > smallList.size()) {
        typename list<Type>::iterator largeIt = largeList.begin();
        typename list<Type>::iterator smallIt = smallList.begin();
        typename list<Type>::iterator returnLargeList = largeIt;

        do{
            // If the character of smallList matches the one of largeList,
            // continue comparing the latter character.
            if(*largeIt == *smallIt){
                smallIt++;
                largeIt++;
            }
            // If the character of smallList doesn't match with the one in largeList,
            // restart the comparison by setting smallIt to point to the first node/character of smallList again.
            // Also setting largeIt to point to the second (next after the starting character of previous comparison)
            // character of largeList.
            else{
                smallIt = smallList.begin();
                largeIt = ++returnLargeList;
            }
        } while(largeIt != largeList.end() && smallIt != smallList.end());

        // If smallIt points to the past-the-end element of smallList,
        // this proves that smallList is sublist of largeList.
        if(smallIt == smallList.end())
            return true;
        else
            return false;
    }
    // ELse if smallList has larger size than largeList, return false.
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::fibonacciSearch(Type arrListSorted[], int num, const Type& item){
    // Second value of fibonacci sequence.
    int fibN_1 = 1;
    // First value of fibonacci sequence.
    int fibN_2 = 0;
    int fib = fibN_1 + fibN_2;

    // Determine the smallest fibonacci number (0, 1,....) greater or equal to num.
    while(fib < num){
        fibN_2 = fibN_1;
        fibN_1 = fib;
        fib = fibN_1 + fibN_2;
    }

    // Offset: used to indicate elements in arrListSorted to be eliminated (index: 0 -> offset)
    int offset = -1;

    while(fib > 1){
        int index = min(fibN_2 + offset, num - 1);

        // One step down fibonacci sequence if the element pointed is less than item.
        if(arrListSorted[index] < item){
            fib = fibN_1;
            fibN_1 = fibN_2;
            fibN_2 = fib - fibN_1;
            // Updating offset.
            offset = index;
        }

        // Two steps down the fibonacci sequence if element pointed is larger than item.
        else if(arrListSorted[index] > item){
            fib = fibN_2;
            fibN_1 = fibN_1 - fibN_2;
            fibN_2 = fib - fibN_1;
        }

        // If match, return true.
        else
            return true;
    }

    // Since there might be one element left in arrListSorted,
    // if the value if equal to item, return true.
    if(fib && arrListSorted[offset+1] == item)
        return true;
    return false;
}

template <class Type>
bool SearchingAlgo<Type>::recursiveLinearSearch(Type arrList[], int num, const Type& item){
    return recursiveLinearSearch(arrList, 0, num - 1, item);
}

template <class Type>
bool SearchingAlgo<Type>::recursiveLinearSearch(Type arrList[], int startIn, int endIn, const Type& item){
        if(startIn <= endIn)
            return arrList[startIn] == item || recursiveLinearSearch(arrList, startIn + 1, endIn, item);
        else
            return false;
}

template <class Type>
bool SearchingAlgo<Type>::recursiveSublistSearch(list<Type>& largeList, list<Type>& smallList){
    return recursiveSublistSearch(largeList, largeList.begin(), largeList.begin(), smallList, smallList.begin());
}

template <class Type>
bool SearchingAlgo<Type>::recursiveSublistSearch(list<Type>& largeList, typename list<Type>::iterator largeIt, typename list<Type>::iterator startLoc,
                                                 list<Type>& smallList, typename list<Type>::iterator smallIt){
    if(smallIt == smallList.end())
        return true;
    else if(largeIt == largeList.end())
        return false;
    else {
        if(*largeIt == *smallIt)
            return recursiveSublistSearch(largeList, ++largeIt, startLoc, smallList, ++smallIt);
        else
            return recursiveSublistSearch(largeList, ++startLoc, startLoc, smallList, smallList.begin());
    }
}

#endif // SEARCHINGALGO.H

