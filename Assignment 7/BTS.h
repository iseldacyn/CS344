#ifndef BTS_H_INCLUDED
#define BTS_H_INCLUDED

template <typename Value> 
struct Answer 
{ 
  bool isFound; // true if key exists 
  Value value; 
  Answer() {}; 
  Answer(bool b) {isFound = b;} 
  Answer(bool b, Value v) {isFound = b; value = v;} 
}; 

template <typename Key, typename Value> 
struct BST_node 
{ 
    Key key; 
    Value value; 
    int n;  // size of subtree rooted here 
    BST_node *left;  // pointer to left subtree 
    BST_node *right;  // pointer to right subtree 
    BST_node() {}; 
    BST_node(Key k, Value v, int sz, BST_node *l, BST_node *r) {key=k; value=v; n=sz, left=l; right=r;} 
}; 

template <typename Key, typename Value> 
class map 
{ 
private: 
  BST_node<Key,Value> *root; 
  int size(BST_node<Key,Value> *p) {if (p==NULL) return 0; else return p -> n;}
  Answer<Value> get(BST_node<Key,Value> *p,Key k); // p is pointer to node we are at
  // put returns pointer to root of tree
  BST_node<Key,Value> *put(BST_node<Key,Value> *p, Key k,Value v);
  BST_node<Key,Value>*min(BST_node<Key,Value> *p){ if (p -> left == NULL)  
      return p;  
    else  
    return min(p -> left);} 
  // deleteMin deletes smallest key and returns root 
  BST_node<Key,Value> *deleteMin(BST_node<Key,Value> *p); 
public: 
  int size() {return size(root);} 
  bool isEmpty() {return root == NULL;} 
  map() {root = NULL;}   // initialize to empty tree 
  Answer<Value> get(Key k) {return get(root,k);}
  void put(Key k, Value v) {root = put(root,k,v);}
  Answer<Key> min() { if (root == NULL)  
    return Answer<Key>(false);  
  else  
    return Answer<Key>(true,min(root)->key);}
  // deleteMin deletes smallest key 
  void deleteMin() {if (root != NULL) root = deleteMin(root);} 
  friend void printOut(BST_node *p);
}; 

template<typename Key, typename Value> 
BST_node<Key,Value> *map<Key,Value>::put(BST_node<Key,Value> *p, Key k,Value v) 
{ 
  if (p == NULL)  // not there, so add it 
     return new BST_node<Key,Value>(k,v,1,NULL,NULL);     
  else if (k < p -> key) 
    p -> left = put(p -> left, k, v);   
  else if (k > p -> key) 
    p -> right = put(p -> right, k, v);   
  else 
    p -> value = v;  // update value 
  p -> n = size(p -> left) + size(p -> right) + 1;  // update size 
  return p; 
} 

template<typename Key, typename Value> 
Answer<Value> map<Key,Value>::get(BST_node<Key,Value> *p, Key k) 
{ 
  if (p == NULL) 
    return Answer<Value>(false); 
  else if (k < p -> key) 
    return get(p -> left, k); 
  else if (k > p -> key) 
    return get(p -> right, k); 
  else 
    return Answer<Value>(true,p -> value); 
} 

// deletes the smallest key 
template<typename Key, typename Value> 
BST_node<Key,Value> *map<Key,Value>::deleteMin(BST_node<Key,Value> *p) 
{ 
  if (p -> left == NULL)  // found min 
  { 
    BST_node<Key,Value> *r = p -> right; 
    delete p;   
    return r;  // return right child 
  } 
  p -> left = deleteMin(p -> left); 
  p -> n = size(p -> left) + size (p -> right) + 1; 
  return p; 
} 

template<typename Key, typename Value> 
void print(const map<Key,Value> &A){
  if(A->root == NULL){cout << '.\n';}
  else{printOut(A->root);}
}

#endif