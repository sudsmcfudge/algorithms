#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int *mergeSort(int *, int, long int &);

int main()
{

  ifstream myfile;
  string line;
  
  int *a,*b,i;

  //  int n = 65536;

  
  int n = 100000;
  long int n_inv = 0;

  a = new int [n];

  myfile.open("IntegerArray.txt");

  for (i=0; i<n; i++){
    myfile >> a[i];
  }

  
  //  int *b,i;
  //  long int n_inv = 0;

  //  int n = 4;

  //  a = new int [n];

  //  int a[] = {3, 1, 0, 2};


  //  for (i=0; i<n; i++){
  //    cout << a[i] << endl;
  //  }

  myfile.close();
  //  cout << endl;

  //  for (i=0; i<n; i++) cout << a[i] << endl;
  //  cout << endl;

  b = mergeSort(a,n,n_inv);

  //  for (i=0; i<n; i++) cout << b[i] << endl;

  //  cout << endl;

  cout << n_inv << endl;
  
  return 0;

}

int *mergeSort(int *in, int n, long int &n_inv)
{
  int *merge(int *, int *, int, long int &);

  int *a,*b,*c,*d,*out,temp;
  int na,nb;

  //  cout << n_inv << endl;

  //  c = new int[n/2];
  //  d = new int[n/2];
  //  out = new int[n];

  // odd
  if (n%2){
    na = n/2 + 1;
    nb = n/2;
  }
  // even
  else {
    na = n/2;
    nb = n/2;
  }

  if (n > 2){
    a = &(in[0]);
    b = &(in[na]);
    c = mergeSort(a, na, n_inv);
    d = mergeSort(b, nb, n_inv);
    out = merge(c,d,n,n_inv);
  }
  else {
    out = new int[n];

    if (n==1){
      out[0] = in[0];
    }

    else if (in[0] < in[1]){
      out[0] = in[0];
      out[1] = in[1];
    }
    else {
      out[0] = in[1];
      out[1] = in[0];
      //*n_inv = *n_inv + 1;
      n_inv++;
    }
  }

  return out;
}

int *merge(int *a, int *b, int n, long int &n_inv)
{
  // len a >= len b 
  // c length n
  // so if odd
  // len a == n/2 + 1
  // len b == n/2
  int i,j,na,nb,*c;
  i = j = 0;

  // odd
  if (n%2){
    na = n/2 + 1;
    nb = n/2;
  }
  // even
  else {
    na = n/2;
    nb = n/2;
  }

  c = new int[n];

  for(int k=0; k<n; k++){
    
    if (i == na){
      c[k] = b[j];
      j++;
    }
    else if (j == nb){
      c[k] = a[i];
      i++;
    }
    else {
      if (a[i] < b[j]){
	c[k] = a[i];
	i++;
      }
      else{
	c[k] = b[j];
	j++;
	n_inv = n_inv + na - i;
      }
    }
  }
  return c;
}
  
