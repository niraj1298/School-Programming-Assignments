/*
Programming Assignment #5: Dual-Pivot Quicksort( Vladimir Yaroslavskiy's Algorithm )
 Developer: Niraj Nepal
 Date: 11/01/2022
 Description:
 Credits:
*/
#include <time.h>
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;

//For this program, you are to implement the dual-pivot quicksort algorithm from class in C++ and to make it as efficient as possible.
//You are to use the following algorithm as a guide:
//1. For small arrays (length < 27), use the Insertion sort algorithm.
//2. Choose two pivot elements P1 and P2. We can get, for example, the first element a[left] as P1 and the last element a[right] as P2.
//3. P1 must be less than P2, otherwise they are swapped. So, there are the following parts:
// - part I with indices from left+1 to L–1 with elements, which are less than P1,
// - part II with indices from L to K–1 with elements, which are greater or equal to P1 and less or equal to P2,
// - part III with indices from G+1 to right–1 with elements greater than P2,
// - part IV contains the rest of the elements to be examined with indices from K to G.
//4. The next element a[K] from the part IV is compared with two pivots P1 and P2, and placed to the corresponding part I, II, or III.
//5. The pointers L, K, and G are changed in the corresponding directions.
//6. The steps 4 - 5 are repeated while K ≤ G.
//7. The pivot element P1 is swapped with the last element from part I, the pivot element P2 is swapped with the first element from part III.
//8. The steps 1 - 7 are repeated recursively for every part I, part II, and part III.

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

    //If P1 is greater than P2, swap them
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
    //Initialize array
    int arr[] = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    int size = sizeof(arr) / sizeof(arr[0]);


    //Print array before sorting
    cout<< "Array before sorting: ";
    printArray(arr, size);

    auto start = high_resolution_clock::now();
    //Sort array using dual-pivot quicksort algorithm
    dualPivotQuickSort(arr, 0, size - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    //Print array after sorting
    cout<< "Array after sorting: ";
    printArray(arr, size);
    cout<<endl;
    cout << duration.count() << " nanoseconds." << endl;

    return 0;
}
