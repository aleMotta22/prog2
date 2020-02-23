#include <iostream>
#include <fstream>
#define DIM 1000
using namespace std;

template <class T> class Pila{
private:
	int head;
	T vett[DIM];
public:
    Pila(){
    	head=0;
	}
	void insertP(const T& x){
		vett[head]=x;
		head++;
	}
	void stampaP(ofstream& out,int n){
		for(int j=n-1; j>=0; j--){
		out<<vett[j]<< " ";
	    }
    }
};

int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i=0; i<100;i++){
		string tipo; in>>tipo;
		int n; in>>n;
		if(tipo=="int"){
		   Pila<int>* P=new Pila<int>();
		   int x;
		   for(int j=0; j<n;j++){
			in >> x;
			P->insertP(x);
		   }
		   P->stampaP(out,n);
		   out<<endl;
		}
	    else if(tipo=="double"){
		   Pila<double>* P=new Pila<double>();
		   double x;
		   for(int j=0; j<n;j++){
			in >> x;
			P->insertP(x);
		   }
		   P->stampaP(out,n);
		   out<<endl;
		}
		else if(tipo=="bool"){
		   Pila<bool>* P=new Pila<bool>();
		   bool x;
		   for(int j=0; j<n;j++){
			in >> x;
			P->insertP(x);
		   }
		   P->stampaP(out,n);
		   out<<endl;
		}
		else if(tipo=="char"){
		   Pila<char>* P=new Pila<char>();
		   char x;
		   for(int j=0; j<n;j++){
			in >> x;
			P->insertP(x);
		   }
		   P->stampaP(out,n);
		   out<<endl;
	    }       
	}
	
	
}
