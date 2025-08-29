#ifndef COLLECTION_SORTING_HEADER
#define COLLECTION_SORTING_HEADER

#include <iostream>
#include <vector>
#pragma once
#include <assert.h>
#include "merge.h"
#include "bubble.h"
#include "quick.h"
#include "select.h"
#include "heap.h"
#include "insertion.h"
#include "helper.h"

namespace collection_sorting {
using namespace std;

class ShellSort {};


void Launcher(){

    std::cout << "================================ Merge sort \n";
    MergeSort ms;;
    vector<int> vec_ms = {12, 11, 13, 5, 6, 7};
    ms.mergeSortRecursive<int>(vec_ms, 0, vec_ms.size() - 1);
    PrintVector<int>(vec_ms);

    std::cout << "================================ bubble sort \n";
    BubbleSort bs;;
    vector<int> vec_bs = {12, 11, 13, 5, 6, 7};
    bs.Solver(vec_bs);
    PrintVector(vec_bs);

    std::cout << "================================ quick sort \n";
    QuickSort qs;;
    vector<int> vec_qs = {12, 11, 13, 5, 6, 7};
    qs.quick_sort<int>(vec_qs, 0, vec_qs.size() - 1);
    PrintVector(vec_qs);

    std::cout << "================================ select sort \n";
    SelectSort ss;;
    vector<int> vec_ss = {12, 11, 13, 5, 6, 7};
    ss.Solver<int>(vec_ss);
    PrintVector(vec_ss);

    std::cout << "================================ heap sort \n";
    HeapSort hs;;
    vector<int> vec_hs = {12, 11, 13, 5, 6, 7};
    hs.Solver<int>(vec_hs);
    PrintVector(vec_hs);

    std::cout << "================================ insertion sort \n";
    InsertionSort is;;
    vector<int> vec_is = {12, 11, 13, 5, 6, 7};
    is.Solver(vec_is);
    PrintVector(vec_is);

}

} // namespace collection_sorting
#endif // COLLECTION_SORTING_HEADER
