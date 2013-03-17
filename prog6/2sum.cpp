#include <iostream>
#include <fstream>
#include <list>

using namespace std;

const int N = 173141; // far from power of 2, 10, prime

class HashTable
{
  // array of list pointers
  list<int> *buckets[N];
  int hashFunc(int);
public:
  HashTable();
  void insert(int);
  void print();
  bool lookup(int);
};

void HashTable::print()
{
  list<int> *a;

  for (int i=0; i<N; i++){
    a = buckets[i];
    cout << i << "\t";
    for (list<int>::iterator it=a->begin(); it!=a->end(); ++it){
      cout << *it << " ";
    }
    cout << endl;
  }
}

int HashTable::hashFunc(int x)
{
  // numbers go from
  // 0 - 9999999

  if (x < 0){
    return 0;
  }

  return x % N;
}

HashTable::HashTable()
{
  list<int> *tmpPtr;
  // initialize array to point to empty lists
  for (int i=0; i<N; i++){
    tmpPtr = new list<int>; // allocate pointers
    buckets[i] = tmpPtr;
  }  
}

void HashTable::insert(int x)
{
  // use hash function to fill a bucket

  int i;

  // hash to a bucket i
  i = hashFunc(x);

  // insert in list
  buckets[i]->push_back(x);

}

bool HashTable::lookup(int x)
{
  int i;
  list<int> *a;

  // find bucket
  i = hashFunc(x);
  a = buckets[i];

  // look for it
  for (list<int>::iterator it=a->begin(); it!=a->end(); ++it){
    if (x == *it){
      return true;
    }
  }

  return false;
}
  

int main()
{
  ifstream myfile;
  HashTable *table = new HashTable();
  int i,x,y,t,sum;
  bool btest;

  int n = 500000;
  
  int *a = new int[n];
  bool *b = new bool[1501]; // keep track of t's found

  //initialize b
  for (i=0; i<1501; i++){
    b[i] = false;
  }
  
  myfile.open("HashInt.txt");

  for (i=0; i<n; i++){
    myfile >> x;
    a[i] = x;
    table->insert(x);
  }

  myfile.close();

  for (i=0; i<n; i++){
    //    if (i%100 == 0){
    //      cout << i << endl;
    //    }

    x = a[i];
    
    // looking for 2500 <= t <= 4000 
    // 2500 - x <= t-x <= 4000 - x
    // 2500 - x <=  y  <= 4000 - x

    for (y=2500-x; y<=4000-x; y++){
      btest = table->lookup(y);
      
      if (btest && x!=y){
	t = x+y;
	b[t-2500] = true;
	cout << x << " " << y << " " << t << endl;
      }
      
    }

  }

  cout << "done" << endl;
  
  sum = 0;

  for (i=0; i<1501; i++){
    if (b[i]){
      cout << i+2500 << " ";
      sum++;
    }
  }

  cout << endl;
  cout << "sum: " << sum << endl;

  //  table->print();



}
    
