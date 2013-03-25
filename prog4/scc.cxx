#include <iostream>
#include <fstream>
#include <list>

using namespace std;

const int nVertices = 875714;
//const int nVertices = 9;

class Stack // LIFO
{
  list <int> stack;
public:
  void push(int);
  int pop();
};

int t;
int sstar;

//int *ft;
Stack ft;
int *leaders;


void Stack::push(int x)
{
  stack.push_front(x);
}

int Stack::pop()
{
  int x;
  x = stack.front();
  stack.pop_front();
  return x;
}


class Graph // adjacency list
{
  list<int> *adjlist[nVertices+1];
public:
  Graph();
  bool explored[nVertices+1];
  void add(int, int);
  void print();
  void dfs(int);
};

void Graph::dfs(int s)
{
  list<int> *row;
  int v;
  row = adjlist[s];
  
  explored[s] = true;
  leaders[s] = sstar;

  // loop over edges
  for (list<int>::iterator it=row->begin(); it!=row->end(); ++it){
    v = *it;
    if (!explored[v]){
      dfs(v);
    }
  }

  if (t < nVertices){
    t++;
    ft.push(s);
  }
  //  ft[s] = t;

}

void Graph::print()
{
  list<int> *row;

  for (int i=1; i<=nVertices; i++){ // i=1:n
    row = adjlist[i];
    cout << i << "\t";
    for (list<int>::iterator it=row->begin(); it!=row->end(); ++it){
      cout << *it << ",";
    }
    cout << endl;
  }
}

void Graph::add(int i, int x)
{
  adjlist[i]->push_back(x);
}

Graph::Graph()
{
  list<int> *tmpPtr;

  //  explored = new bool[nVertices];
  //  explored = explored--;

  // initialize array to point to empty lists
  for (int i=1; i<=nVertices; i++){ // i=1:n
    tmpPtr = new list<int>; // allocate pointers
    adjlist[i] = tmpPtr;

    explored[i] = false;

  }  
}

int median(int a[], int n)
{
  int i,ind,max;
  int b[n+1];

  for (i=1; i<=n; i++){
    b[i] = 0;
  }

  for (i=1; i<=n; i++){
    if (a[i] >= 0){
      b[a[i]]++;
    }
  }

  max = -1;

  for (i=1; i<=n; i++){
    if (b[i] > max){
      max = b[i];
      ind = i;
    }
  }

  return a[ind];

}

int main()
{
  ifstream myfile;
  Graph *graph = new Graph();
  Graph *grev  = new Graph();
  int i,ind,x,m,count;

  //  ft = new int[nVertices];
  //  ft = ft--;

  leaders = new int[nVertices];
  leaders = leaders--;

  myfile.open("SCC.txt");
  // myfile.open("test.txt");

  if (myfile.is_open()){
    while ( myfile.good() ){
      myfile >> i;
      myfile >> x;
      graph->add(i,x);
      grev->add(x,i);
    }
  }

  //  graph->print();
  //  graph->dfs(1);

  // DFS-Loop
  t = 0;
  sstar = NULL;

  //  grev->print();
  
  for (i=nVertices; i>=1; i--){
    if (!grev->explored[i]){
      sstar = i;
      grev->dfs(i);
    }
  }

  //  t = 0;
  //  sstar = NULL;

  for (i=nVertices; i>=1; i--){
    //    ind = ft[i];
    ind = ft.pop();
    if (!graph->explored[ind]){
      sstar = ind;
      graph->dfs(ind);
    }
  }

  for (ind=0; ind<5; ind++){
    count = 0;
    m = median(leaders,nVertices);
    
    cout << m << ":";
    
    for (i=1; i<=nVertices; i++){
      if (leaders[i] == m){
	leaders[i] = -1;
	count++;
      }
    }
    
    cout << count << endl;

  }

  myfile.close();

}
