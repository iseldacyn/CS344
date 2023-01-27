#include<iostream>
using namespace std;

struct Data{
  int key;
  char data;
  Data(int a, char b): key(a), data(b) {}
  Data(): key(0), data(0) {}
  Data operator =(Data &a){
    key = a.key; data = a.data;
    return *this;
  }
  bool operator ==(const Data &a){
    return key == a.key;
  }
  bool operator>(const Data &a){
    return key > a.key;
  }
  bool operator<(const Data &a){
    return key < a.key;
  }
  bool operator>=(const Data &a){
    return key >= a.key;
  }
  bool operator<=(const Data &a){
    return key <= a.key;
  }
};

ostream& operator<<(ostream& os, const Data& a){
  os << a.key << a.data << " ";
  return os;
}
 
template <typename T> 
void exchange(T A[], int i, int j) 
{ 
  T t = A[i];
  A[i] = A[j];
  A[j] = t;
} 

void printarr(Data A[], int sz){
  for(int i = 0; i < sz; i++)
  cout << A[i];
  cout << '\n';
}

template <typename T> 
int partition(T A[], int lo, int hi) 
{ 
  int i=lo, j=hi+1; 
  T v = A[lo];
  while (true) 
  { 
    while (A[++i] < v) 
      if (i == hi) 
        break; 
    while (v < A[--j]) 
      if (j == lo) 
        break; 
    if (i >= j) 
      break; 
    exchange(A,i,j); 
  } 
  exchange(A,lo,j);
  return j; 
} 

template <typename T> 
void quickSort(T A[], int lo, int hi) 
{ 
  if (hi <= lo) 
    return; 
  int j = partition(A,lo,hi); 
  quickSort(A,lo,j-1); 
  if (lo == 0 && hi == 7) printarr(A,8);
  quickSort(A,j+1,hi); 
} 

template <typename T> 
void quickSort3(T A[], int lo, int hi) 
{ 
  if (hi <= lo) 
    return; 
  int lt = lo, i = lo+1, gt = hi; 
  T v = A[lo]; 
  while (i <= gt) 
  { 
    if (A[i] < v) 
      exchange(A,lt++,i++); 
    else if (A[i] > v) 
      exchange(A,i,gt--); 
    else 
      i++; 
  } 
  quickSort3(A,lo,lt-1); 
  if (lo == 0 && hi == 7) printarr(A,8);
  quickSort3(A,gt+1,hi); 
} 

int main(){
  Data a[8] = {{2,'A'}, {4,'V'}, {2,'B'}, {1,'T'}, {2,'C'}, {0,'S'}, {2,'D'}, {3,'U'}};

  quickSort(a, 0, 7);

  return 0;
}