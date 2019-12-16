#include <iostream>
#include <fstream>

using namespace std;



template<class T> class Nodo{
	private:
		T val;
		Nodo<T>* succ;
	public:
		Nodo(T x){
			val=x;
			succ=NULL;
		}
		void setNodo(T x){ val=x; }
		void setSucc(Nodo<T>* x){ succ=x; }
		Nodo<T>* getSucc(){ return succ; }
		T getVal(){ return val; }
};


template <class T> class Pila{
	private:
		Nodo<T>* p; 
	public:
	    Pila(){ p=NULL; }
		void svuotaPila(){p=NULL;}
	    void pilaVuota(){return p==NULL;}
	Pila<T>* Push(T x){
		Nodo<T> *aux=new Nodo<T>(x);
		if(p) aux->setSucc(p);
		p=aux;
		return this;
	}; 
	void Pop(){
		Nodo<T>* aux;
		if(p){
			aux=p;
		    p=p->getSucc();
		    delete aux;
	    }
	}
	void StampaPila(){
		Nodo<T>* pnodo=p; 
	
	    if (pnodo==NULL) 
		    cout << "Pila vuota!" << endl;
	    while(pnodo!=NULL) {
	     	cout << pnodo->getVal() << endl; 
	    	pnodo=pnodo->getSucc(); 
	    }
	}
	void StampaPila(ofstream &out){
		Nodo<T>* pnodo=p; 
	
	    if (pnodo==NULL) 
		    out << "Pila vuota!" << endl;
	    while(pnodo!=NULL) {
	     	out << pnodo->getVal() << " "; 
	    	pnodo=pnodo->getSucc(); 
	    }
	    out<<endl;
	}
	
};

void soluzione(ofstream &out, ifstream &in){
	string tipo; in >> tipo;
	int n; in >> n;
	char c;
	string tmp;
	if(tipo=="int"){
		int val;
		Pila<int>* p=new Pila<int>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->Push(val);
		    }
		    else{
		    	p->Pop();
		    	in>>tmp;
			}
		}
		p->StampaPila(out);
	}
	if(tipo=="double"){
		double val;
		Pila<double>* p=new Pila<double>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->Push(val);
		    }
		    else{
		    	p->Pop();
		    	in>>tmp;
			}
		}
		p->StampaPila(out);
	}
	if(tipo=="char"){
		char val;
		Pila<char>* p=new Pila<char>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->Push(val);
		    }
		    else{
		    	p->Pop();
		    	in>>tmp;
			}
		}
		p->StampaPila(out);
	}
	if(tipo=="bool"){
		bool val;
		Pila<bool>* p=new Pila<bool>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->Push(val);
		    }
		    else{
		    	p->Pop();
		    	in>>tmp;
			}
		}
		p->StampaPila(out);
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i=0; i<100; i++)
	   soluzione(out,in);
}
