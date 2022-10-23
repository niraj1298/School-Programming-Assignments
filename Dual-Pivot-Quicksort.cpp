/*
Programming Assignment #5: Dual-Pivot Quicksort( Vladimir Yaroslavskiy's Algorithm )
 Developer: Niraj Nepal
 Date: 11/01/2022
 Description: Implementation of Vladmir Yaroslavskiy's Algorithm for Dual-Pivot Quicksort, then compare it with the built in sort function in C++.
 Credits: Vladimir Yaroslavskiy's Algorithm for Dual-Pivot Quicksort, C++ Documentation, and StackOverflow ( for helping fix some errors ).
*/
#include <time.h>
#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std::chrono;
using namespace std;

//Function to swap two elements
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Function to print array
void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout<< arr[i] << " ";
    }
    cout<< endl;
}

//Function to sort array using dual-pivot quicksort algorithm
void dualPivotQuickSort(int arr[], int left, int right){
    //If the array has less than 27 elements, use insertion sort
    if(right - left < 27){
        for(int i = left + 1; i <= right; i++){
            int temp = arr[i];
            int j = i - 1;
            while(j >= left && arr[j] > temp){
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
        return;
    }

    //Choose two pivot elements P1 and P2
    int p1 = arr[left];
    int p2 = arr[right];

    //If P1 is greater than P2, swap them /*fix */
    if(p1 > p2){
        swap(&p1, &p2);
    }

    //Initialize pointers L, K, and G
    int L = left + 1;
    int K = left + 1;
    int G = right - 1;

    //Loop until K is greater than G
    while(K <= G){
        //If the element at K is less than P1, swap it with the element at L and increment L and K
        if(arr[K] < p1){
            swap(&arr[L], &arr[K]);
            L++;
            K++;
        }
            //If the element at K is greater than P2, swap it with the element at G and decrement G
        else if(arr[K] > p2){
            swap(&arr[K], &arr[G]);
            G--;
        }
            //If the element at K is greater than or equal to P1 and less than or equal to P2, increment K
        else{
            K++;
        }
    }

    //Swap P1 with the last element from part I and P2 with the first element from part III
    L--;
    G++;
    swap(&arr[left], &arr[L]);
    swap(&arr[right], &arr[G]);

    //Recursively sort part I, part II, and part III
    dualPivotQuickSort(arr, left, L - 1);
    dualPivotQuickSort(arr, L + 1, G - 1);
    dualPivotQuickSort(arr, G + 1, right);
}

//Driver function
int main(){
    cout<<"////////////////////////////////////////////////////////////"<<endl;
    cout<< "[ Tests 1 - 4 sorted with Dual-Pivot Quicksort Algorithm ]" << endl;
    cout<<"////////////////////////////////////////////////////////////"<<endl;
    //test 1 small array
    int arr[] = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    int size = sizeof(arr) / sizeof(arr[0]);


    auto start = high_resolution_clock::now();
    //Sort array using dual-pivot quicksort algorithm
    dualPivotQuickSort(arr, 0, size - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout<<endl;
    cout << "Test 1 Small array: " <<duration.count() << " nanoseconds." << endl;


    //test 2 large array
    int arr2[100000];
    for(int i = 0; i < 100000; i++){
        arr2[i] = rand() % 100000;
    }
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    auto start2 = high_resolution_clock::now();
    //Sort array using dual-pivot quicksort algorithm
    dualPivotQuickSort(arr2, 0, size2 - 1);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);

    cout << "Test 2 Large array: " << duration2.count() << " milliseconds." << endl;

    //test 3 large with only 0's array
    int arr3[10000];
    for(int i = 0; i < 10000; i++){
        arr3[i] = 0;
    }
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    auto start3 = high_resolution_clock::now();
    //Sort array using dual-pivot quicksort algorithm
    dualPivotQuickSort(arr3, 0, size3 - 1);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);

    cout << "Test 3 Large array with only 0's: " << duration3.count() << " microseconds." << endl;

    //test 4 large with only 1's array
    int arr4[10000];
    for(int i = 0; i < 10000; i++){
        arr4[i] = 1;
    }
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    auto start4 = high_resolution_clock::now();
    //Sort array using dual-pivot quicksort algorithm
    dualPivotQuickSort(arr4, 0, size4 - 1);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4 - start4);

    cout << "Test 4 Large array with only 1's: " << duration4.count() << " microseconds." << endl;

    cout<<endl;
    cout<<"////////////////////////////////////////////////////////////"<<endl;
    cout<< "[ Tests 1 - 4 sorted with the built in c++ sorting method ]" << endl;
    cout<<"////////////////////////////////////////////////////////////"<<endl;
    cout<<endl;

  //Test 1 with built in c++ sorting method
    int arr5[] = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    auto start5 = high_resolution_clock::now();
    //Sort array using dual-pivot quicksort algorithm
    sort(arr5, arr5 + size5);
    auto stop5 = high_resolution_clock::now();
    auto duration5 = duration_cast<nanoseconds>(stop5 - start5);

    cout << "Test 1 Small array " << duration5.count() << " nanoseconds." << endl;


    //Test 2 with built-in c++ sorting method
    int arr6[100000];
    for(int i = 0; i < 100000; i++){
        arr6[i] = rand() % 100000;
    }
    int size6 = sizeof(arr6) / sizeof(arr6[0]);
    auto start6 = high_resolution_clock::now();
    //Sort array using sorting algorithm
    sort(arr6, arr6 + size6);
    auto stop6 = high_resolution_clock::now();
    auto duration6 = duration_cast<milliseconds>(stop6 - start6);

    cout << "Test 2 Large array: " << duration2.count() << " milliseconds." << endl;

    //Test 3 with built-in c++ sorting method
    int arr7[10000];
    for(int i = 0; i < 10000; i++){
        arr7[i] = 0;
    }
    int size7 = sizeof(arr7) / sizeof(arr7[0]);
    auto start7 = high_resolution_clock::now();
    //Sort array using sorting algorithm
    sort(arr7, arr7 + size7);
    auto stop7 = high_resolution_clock::now();
    auto duration7 = duration_cast<microseconds>(stop7 - start7);

    cout << "Test 3 Large array with only 0's: " << duration7.count() << " microseconds." << endl;

    //Test 4 with built-in c++ sorting method
    int arr8[10000];
    for(int i = 0; i < 10000; i++){
        arr8[i] = 1;
    }
    int size8 = sizeof(arr8) / sizeof(arr8[0]);
    auto start8 = high_resolution_clock::now();
    //Sort array using sorting algorithm
    sort(arr8, arr8 + size8);
    auto stop8 = high_resolution_clock::now();
    auto duration8 = duration_cast<microseconds>(stop8 - start8);

    cout << "Test 4 Large array with only 1's: " << duration8.count() << " microseconds." << endl;

    return 0;
}
