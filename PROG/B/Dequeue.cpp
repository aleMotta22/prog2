#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Nodo{
	private:
		T val;
		Nodo<T>* succ;
	public:
		Nodo(T x){
		val=x; 
		succ=NULL; }
        void setVal(T x){ val=x; }
        void setSucc(Nodo<T>* p){ succ=p; }
        T getVal(){ return val;}
        Nodo<T>* getSucc(){ return succ;}
};

template <class T> class Coda{
    private:
   	    Nodo<T>* testa;
		Nodo<T>* fine;
    public:
	    Coda(){ testa=fine=NULL; }
	    
	    bool eVuota(){ return testa==NULL; }
	    
		void insertQ(T x){
			Nodo<T>* qnodo= new Nodo<T>(x);
			if(eVuota())
				testa=fine=qnodo;
			else{
				fine->setSucc(qnodo);
				fine=qnodo;
			}
		}
		
		void Cancella(){
			if(eVuota()) cout << "Coda Vuota!";
			Nodo<T>* aux;
			aux=testa;
			testa=testa->getSucc();
			delete aux;
		}
		
		void stampaCoda(ofstream& out){
			if(!eVuota()){
				Nodo<T>* aux=testa;
				while(aux){
					out<<aux->getVal()<<" ";
					aux=aux->getSucc();
				}
				out<<endl;
			}
		}
};
void soluzione(ifstream& in, ofstream& out){
	string tipo; in >> tipo;
	int n; in >> n;
	char c;
	string tmp;
	if(tipo=="int"){
		int val;
		Coda<int>* p=new Coda<int>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->insertQ(val);
		    }
		    else{
		    	p->Cancella();
		    	in>>tmp;
			}
		}
		p->stampaCoda(out);
	}
	if(tipo=="double"){
		double val;
		Coda<double>* p=new Coda<double>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->insertQ(val);
		    }
		    else{
		    	p->Cancella();
		    	in>>tmp;
			}
		}
		p->stampaCoda(out);
	}
	if(tipo=="char"){
		char val;
		Coda<char>* p=new Coda<char>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->insertQ(val);
		    }
		    else{
		    	p->Cancella();
		    	in>>tmp;
			}
		}
		p->stampaCoda(out);
	}
	if(tipo=="bool"){
		bool val;
		Coda<bool>* p=new Coda<bool>();
		for(int i=0; i<n; i++){
			in >> c;
			if(c=='i'){
			   in >> val;
			   p->insertQ(val);
		    }
		    else{
		    	p->Cancella();
		    	in>>tmp;
			}
		}
		p->stampaCoda(out);
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
	   soluzione(in,out);
	}
