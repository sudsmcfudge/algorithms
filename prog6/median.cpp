#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Heap
{
  vector<int> v;
  void bubbleUp(int);
  void bubbleDown(int);
public:
  void insert(int);
  int extractMin();
  int peek();
  int length();
};

int Heap::length()
{
  return v.size();
}

void Heap::insert(int x){
  v.push_back(x);
  bubbleUp(v.size() - 1); // pass bubbleup with index of last
  
  // debug
  /*
  for (int i=0; i<v.size(); i++){
    cout << v.at(i) << " ";
  }
  cout << endl;
  */
}

int Heap::peek(){
  return v.at(0);
}

void Heap::bubbleUp(int i){
  // bubble up from given level to restore heap condition
  int p,temp;

  if (i < 1){ // at the root
    return;
  }

  // get parent
  p = (i+1)/2 - 1;

  // do comparison
  if (v.at(p) > v.at(i)){
    // swap
    temp = v.at(p);
    v.at(p) = v.at(i);
    v.at(i) = temp;
    // repeat
    bubbleUp(p);
  }

}

int Heap::extractMin(){
  int min,len;
  
  len = v.size();
  
  min = v.at(0);
  v.at(0) = v.at(len-1);
  v.pop_back();
  bubbleDown(0);

  // debug
  /*
  for (int i=0; i<v.size(); i++){
    cout << v.at(i) << " ";
  }
  cout << endl;
  */
  return min;
}


void Heap::bubbleDown(int i){
  
  int c1,c2,j,len,temp;

  len = v.size();
  
  // get childen
  c2 = 2*(i+1);
  c1 = c2 - 1;

  if (c2 < len){ // two children
    // find smallest
    if (v.at(c1) < v.at(c2)){
      j = c1;
    }
    else {
      j = c2;
    }
  }
  else if (c1 < len){ // one child
    j = c1;
  }
  else { // no children
    return;
  }

  // do comparison
  if (v.at(j) < v.at(i)){
    // swap
    temp = v.at(j);
    v.at(j) = v.at(i);
    v.at(i) = temp;
    // repeat
    bubbleDown(j);
  }

}


int main()
{
  Heap heap_low, heap_high;
  int x,y,i,low,high;

  ifstream myfile;
  
  int n = 10000;

  int *median = new int [n];

  myfile.open("Median.txt");

  // first
  myfile >> x;
  median[0] = x;

  // second
  myfile >> y;
  
  if (x < y){
    heap_low.insert(-x); // keep track of max of low ones
    heap_high.insert(y);
    median[1] = x;
  }
  else {
    heap_low.insert(-y);
    heap_high.insert(x);
    median[1] = y;
  }

  for (i=2; i<n; i++){
    myfile >> x;

    low = -heap_low.peek();
    high = heap_high.peek();
    
    if (x < low){
      heap_low.insert(-x);
    }
    else {
      heap_high.insert(x);
    }

    // make sure you are balanced
    if (heap_low.length() - heap_high.length() > 1){
      heap_high.insert(-heap_low.extractMin());
    }
    else if (heap_high.length() - heap_low.length() > 1){
      heap_low.insert(-heap_high.extractMin());
    }

    if (i%2){ // even # of stuff in there
      median[i] = -heap_low.peek();
    }
    else if (heap_low.length() > heap_high.length()){ // odd w/ heap_low bigger
      median[i] = -heap_low.peek();
    }
    else { // odd w/ heap_high bigger
      median[i] = heap_high.peek();
    }

  }

  long long int sum = 0;

  for (i=0; i<n; i++){
    sum += median[i];
  }

  cout << sum << endl;
  cout << sum%10000 << endl;

}
    
