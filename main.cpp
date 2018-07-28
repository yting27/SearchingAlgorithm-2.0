#include <iostream>
#include <SearchingAlgo.h>
#include <ctime>
#include <cstdlib>
#include <list>
using namespace std;

// Demonstrate how the functions in SearchingAlgo class can be used.
int main()
{
    SearchingAlgo<double> objSearch;

    // Declaring sorted array.
    double arrDemo[] = {2.4, 2.7, 3.0, 6.4, 6.5, 8.1};
    // Item to be searched.
    double item = 2.7;
    // To acquire the size of arrDemo.
    int arrSize = sizeof(arrDemo) / sizeof(arrDemo[0]);

    cout << (objSearch.linearSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.binarySearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.jumpSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.exponentialSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.fibonacciSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.exponentialSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.interpolationSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;
    cout << (objSearch.recursiveLinearSearch(arrDemo, arrSize, item) ? "true" : "false") << endl;

    list<double> list1, list2;
    double random;

    // Using time(0) as seed make random number generated more random,
    // reducing the possibility of the same number being generated.
    srand(time(0));

    // Generate 6 nodes containing double values.
    for(int i = 0; i < 6; i++){
        // generate double value within the range of 0.0 to 9.9.
        random = rand() % 100 / 10.0;

        list1.push_back(random);

        // To generate sublist.
        if(i > 2)
            list2.push_back(random);
    }

    cout << (objSearch.sublistSearch(list1, list2) ? "true" : "false") << endl;
    cout << (objSearch.recursiveSublistSearch(list1, list2) ? "true" : "false") << endl;

    return 0;
}
