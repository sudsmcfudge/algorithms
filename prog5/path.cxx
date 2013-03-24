#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

const int nVertices = 200;

class Graph // adjacency list
{
  list<int*> *adjlist[nVertices];
public:
  Graph();
  void add(int, int, int);
  int dijkstra(int);
  void print();
};

bool exist(list<int> a, int i){
  for (list<int>::iterator ip=a.begin(); ip!=a.end(); ++ip){
    if (i == *ip){
      return true;
    }
  }
  return false;
}
  

int Graph::dijkstra(int s)
{
  int i,dmin,v,w,gscore,wstar,vstar,weight;
  list<int> processed;
  int *spd = new int[nVertices];

  spd = spd--;

  for (i=1; i<=nVertices; i++){
    spd[i] = -1;
  }

  // start at s
  processed.push_back(s);
  spd[s] = 0;

  while (processed.size() < nVertices){ //until we reach destination
    list<int*> *row;
    dmin = 1000000;
    // loop over all known vertices
    for (list<int>::iterator ip=processed.begin(); ip!=processed.end(); ++ip){
      v = *ip;
      row = adjlist[v];
      // loop over all unknown edges
      for (list<int*>::iterator it=row->begin(); it!=row->end(); ++it){
	w = (*it)[0];
	weight = (*it)[1];
	gscore = spd[v] + weight;
	if (gscore < dmin && !exist(processed, w)){
	  dmin = gscore;
	  vstar = v;
	  wstar = w;
	}
      }
    }

    if (dmin == 1000000){
      break;
    }

    processed.push_back(wstar);
    spd[wstar] = dmin;
    
  }

  int ind[] = {7,37,59,82,99,115,133,165,188,197};
  
  for (i=0; i<10; i++){
    cout << spd[ind[i]] << ",";
  }
  cout << endl;
  
  /*
  cout << spd[80] << endl;
  cout << spd[92] << endl;
  cout << spd[114] << endl;
  cout << spd[145] << endl;
  */


}

void Graph::print()
{
  list<int*> *row;

  for (int i=1; i<=nVertices; i++){ // i=1:n
    row = adjlist[i];
    cout << i << "\t";
    for (list<int*>::iterator it=row->begin(); it!=row->end(); ++it){
      cout << (*it)[0] << "," << (*it)[1] << " ";
    }
    cout << endl;
  }
}

void Graph::add(int i, int x, int y)
{
  
  int *a = new int[2];
  
  a[0] = x;
  a[1] = y;
  
  adjlist[i]->push_back(a);

}

Graph::Graph()
{
  list<int*> *tmpPtr;
  // initialize array to point to empty lists
  for (int i=1; i<=nVertices; i++){ // i=1:n
    tmpPtr = new list<int*>; // allocate pointers
    adjlist[i] = tmpPtr;
  }  
}
  
int main()
{
  ifstream myfile;
  Graph *graph = new Graph();
  int i,x,y;
  string line;
  char blah;

  myfile.open("dijkstraData.txt");
  //  myfile.open("test.txt");

  if (myfile.is_open()){
    while ( myfile.good() ){
      myfile >> i;
      getline (myfile, line);
      stringstream stream(line);

      while (stream>>x){
	stream>>blah;
	stream>>y;
	graph->add(i,x,y);
      }
    }
  }

  //  graph->print();

  graph->dijkstra(1);

  myfile.close();

}
