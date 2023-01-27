#ifndef PQ_H_INCLUDE
#define PQ_H_INCLUDE

template <typename T> 

class priority_queue { 
private:
    T *A;  // array that holds heap 
    int n;  // size of heap 
    int capacity;  // size of array holding heap 
    void resize(int max){ capacity = max; }
    void exchange(int i, int j); 
    void swim(int k);  // move element up to proper place in heap 
    void sink(int k);  // move element down to proper place in heap 
public: 
    priority_queue(int cap) {A = new T[cap+1], n = 0; capacity = cap;} 
    priority_queue() {A = new T[6], n = 0; capacity = 5;} 
    ~priority_queue() {delete [] A;} 
    bool isEmpty() {return n == 0;} 
    int size() {return n;} 
    void insert(T item); 
    T delMax(); 
    void print();
};

template <typename T> 
void priority_queue<T>::print(){
    for(int i=0;i<capacity;i++)
        std::cout << A[i];
    std::cout << '\n';
}

template <typename T> 
void priority_queue<T>::exchange(int i, int j){
    int temp = i;
    i = j;
    j = i;
}

template <typename T> 
void priority_queue<T>::swim(int k) // index position of out of place element 
{ 
    while (k>1 && A[k/2] < A[k]) // not root and larger than its parent 
    { 
        exchange(k/2,k); // exchange with its parent 
        k = k/2; // move up 
    } 
} 

template <typename T> 
void priority_queue<T>::sink(int k) 
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

template <typename T> 
void priority_queue<T>::insert(T item)  { 
    if (n == capacity) 
        resize(2*capacity); 
    A[++n] = item; 
    swim(n); 
} 

#endif
