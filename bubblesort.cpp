/**
 Developer: Niraj Nepal
 Date: 09/05/2022
 Description: This program is sort any array using bubble sort algorithm.
 Credits: https://www.geeksforgeeks.org/bubble-sort/ (Used to help me understand the algorithm)
 * */
#include <iostream>
using namespace std;

void swap(int *a, int *b) {                                      // swap function
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_Sort(int *low, int *high) {                         // Function to sort an array using bubble sort algorithm
    for (int *j = low; j < high+1; j++) {
        for (int *i = low; i < high; i++) {
            if (*i > *(i + 1)) {
                swap(i, i+1);
            }
        }
    }
}

void reverse(int *low, int *high) {                             // Function to reverse the order of the elements in the array from *low to *high
    for (int *i = low, *j = high; i < j; i++, j--) {
        swap(i, j);
    }
}


void printArray(int *low, int *high) {                          // Function to print an array
    for (int *i = low; i < high+1; i++) {
        cout << *i << " ";
    }
    cout << endl;
}

int main(){
    /* // If you want to take input from user
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int arr[size];

    cout<< "Please fill the array at random: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    */

    int arr[] = {5, 10, 22, 12, 1,4};
    int length = sizeof(arr)/sizeof(arr[0]);
    cout << "Before Sorting: "<<endl;
    printArray(arr,arr+length-1);
    
    bubble_Sort(arr,arr+length-1);
    cout<<"After Sorting: " << endl;
    printArray(arr,arr+length-1);

    reverse(arr,arr+length-1);
    cout << "After Reversing: " << endl;
    printArray(arr,arr+length-1);

    return 0;
}