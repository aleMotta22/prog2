#include<iostream>
#include<fstream>

using namespace std;

template<class T> class MGrafo{
private:
	int len,n,m;
	T **K;
	int **M;
	int trovaIndice(T x){
		for(int i=0; i<n; i++)
			if(*K[i]==x) return i;
		return -1;	
	}
	public:
		MGrafo(int len){
			this->len=len;
			n=m=0;
			K=new T*[len];
			for(int i=0;i<len; i++)
				K[i]=NULL;
			M=new int*[len];
			for(int i=0; i<len; i++){
				M[i]=new int[len];
				for(int j=0; j<len; j++)
					M[i][j]=0;
			}
		}
		MGrafo<T>* addNodo(T val){
			if(n==len) return this;
			if(trovaIndice(val)>=0) return this;
			K[n]=new T(val);
			n++;
			return this;
		}
		MGrafo<T>* addArco(T x, T y){
			int i=trovaIndice(x);
			int j=trovaIndice(y);
			if(i<0 || j<0) return this;
			if(!M[i][j]){
				M[i][j]=1;
				m++;
			}
			return this;
		}
		void stampa(ofstream& out) {
			for(int i=0; i<n; i++) {
				out << "(" << *K[i];
				for(int j=0; j<n; j++) {
					if(M[i][j]) out << ","<< *K[j];
				}
				out<<") ";
			}
			out<<endl;
		}
};

template<typename T> void insertionSort(T a[], int n){
  int i, j;
  T temp;
  int p = 0; 
  for (i = 1; i < n; i++)
  	if (a[p] > a[i]) p = i;
 
  temp = a[0];
  a[0] = a[p];
  a[p] = temp;
 
  for(i = 2; i < n; i++){ 
    j = i;
    while(a[j] < a[j-1]){
       temp = a[j];
       a[j] = a[j-1];
       a[j-1] = temp;
       j--;
       }    
  }
 
}

void soluzione(ifstream& in, ofstream& out){
	int n; in>>n;
	int m; in>>m;
	string tipo; in>>tipo;
	char c;
	if(tipo=="int"){
		MGrafo<int>* g = new MGrafo<int>(150);
		int val;
		int vett[n];
		int n1,n2;
		for(int i=0; i<n; i++){
			in>>val;
			vett[i]=val;
		}
		insertionSort(vett, n);
		for(int i=0; i<n; i++)
			g->addNodo(vett[i]);
		for(int i=0; i<m; i++){
			in>>c;
			in>>n1;
			//in>>c;
			in>>n2;
			in>>c;
			g->addArco(n1,n2);
		}
		g->stampa(out);
	
	}
	if(tipo=="double"){
		MGrafo<double>* g = new MGrafo<double>(150);
		double val;
		double vett[n];
		double n1,n2;
		for(int i=0; i<n; i++){
			in>>val;
			vett[i]=val;
		}
		insertionSort(vett, n);
		for(int i=0; i<n; i++)
			g->addNodo(vett[i]);
		for(int i=0; i<m; i++){
			in>>c;
			in>>n1;
			//in>>c;
			in>>n2;
			in>>c;
			g->addArco(n1,n2);
		}
		g->stampa(out);
	
	}
	if(tipo=="char"){
		MGrafo<char>* g = new MGrafo<char>(150);
		char val;
		char vett[n];
		char n1,n2;
		for(int i=0; i<n; i++){
			in>>val;
			vett[i]=val;
		}
		insertionSort(vett, n);
		for(int i=0; i<n; i++)
			g->addNodo(vett[i]);
		for(int i=0; i<m; i++){
			in>>c;
			in>>n1;
			//in>>c;
			in>>n2;
			in>>c;
			g->addArco(n1,n2);
		}
		g->stampa(out);
	
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
			
}
