#include <iostream>
#include <fstream>
#define DIM 100
using namespace std;

template <class T> class Coda{
private:
	int fronte,fine;
	T vett[DIM];
public:
    Coda(){
    	fronte=1;
    	fine=0;
    	
	}
	void insertQ(const T& x){
		vett[fronte]=x;
		fronte=(fronte+1)%DIM;
	}
	void stampaQ(ofstream& out, int n, int front){
		out<<vett[(front)%DIM]<< " ";
	}	
};

int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100;i++){
		string tipo; in>>tipo;
		int n; in>>n;
		int fronte=1;
		if(tipo=="int"){
		   Coda<int>* Q=new Coda<int>();
		   int x;
		   for(int j=0; j<n;j++){
			in >> x;
			Q->insertQ(x);
			Q->stampaQ(out,n,fronte++);
		   }
		   out<<endl;
		}
	   if(tipo=="double"){
		   Coda<double>* Q=new Coda<double>();
		   double x;
		   for(int j=0; j<n;j++){
			in >> x;
			Q->insertQ(x);
			Q->stampaQ(out,n,fronte++);	
		   }
		   out<<endl;
		}
		 if(tipo=="bool"){
		   Coda<bool>* Q=new Coda<bool>();
		   bool x;
		   for(int j=0; j<n;j++){
			in >> x;
			Q->insertQ(x);
			Q->stampaQ(out,n,fronte++);
		   }
		   out<<endl;
		}
		 if(tipo=="char"){
		   Coda<char>* Q=new Coda<char>();
		   char x;
		   for(int j=0; j<n;j++){
			in >> x;
			Q->insertQ(x);
			Q->stampaQ(out,n,fronte++);
		   }
		   out<<endl;
	    }       
	}
	
	
}
