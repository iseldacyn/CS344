#include<iostream>
#include "Priority_Queue.h"

using namespace std;

void exchange(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void sink(int A[], int k, int size) 
{ 
    while (2*k <= size) // not leaf 
    { 
        int j = 2*k; // make j its left child 
        if (j<size && A[j]<A[j+1]) // if there is another child and other child is bigger 
            j++; // make j its right child 
        if (A[k] >= A[j]) // k >= its biggest child 
            break; 
        exchange(A,k,j); // exchange k with its biggest child 
        k = j; // move k up 
    } 
}

void dispArr(int A[], int size){
    for(int i=0; i<size; i++)
        cout << A[i] << ' ';
    cout << '\n';
} 

template <typename T> 
void heapSort(T A[], int size) 
{ 
    for (int k=size/2; k>=1; k--) 
        sink(A,k,size);
    dispArr(A,11); 
    while (size > 1) 
    { 
        exchange(A,1,size); 
        size--; 
        sink(A,1,size);
        if (size==9 || size==8 || size==7) dispArr(A,11);
    } 
}

int main(){
    int sz = 10;
    int A[11];
    A[0] = 0;
    for(int i=0;i<sz;i++) A[i+1] = i;
    dispArr(A, 11);
    heapSort(A,sz);
    dispArr(A, 11);
}