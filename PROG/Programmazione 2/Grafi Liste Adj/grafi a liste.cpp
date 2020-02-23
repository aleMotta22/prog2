#include<iostream>
#include<fstream>

using namespace std;

class Nodo{
private:
	Nodo* succ;
	int key;
public:
	Nodo(int key){
		this->key=key;
		succ=NULL;
	}
	void setSucc(Nodo* succ){ this->succ=succ; }
	Nodo* getSucc(){ return succ; }
	int getKey(){ return key; }
};

class Lista{
private:
	Nodo* testa,* current;
public:
	Lista(){
		testa=current=NULL;
	}	
	Lista* insert(int val){
		Nodo* newn=new Nodo(val);
		if(!testa) testa = newn;
		else if(testa->getKey()>val){
			newn->setSucc(testa);
			testa=newn;
		}
		else{
			Nodo* tmp=testa;
			while(tmp->getSucc() && tmp->getSucc()->getKey()<=val)
				tmp=tmp->getSucc();
			newn->setSucc(tmp->getSucc());
			tmp->setSucc(newn);
		}
		return this;
	}
	void reset(){ current=testa; }
	int hasNext(){ return current!=NULL;}
	int next(){
		if(hasNext()){
			Nodo* tmp=current;
			current=current->getSucc();
			return tmp->getKey();
		}
		return -1;
	}
	Nodo* search(int val){
		Nodo* tmp=testa;
		while(tmp && tmp->getKey()!=val)
			tmp=tmp->getSucc();
		return tmp;	
	}
};

template<class T> class LGrafo{
private:
	int n,m,len;
	int t,backedge;
	int* c,* d,* in,* f;
	T** K;
	Lista** adj;
	int trovaIndice(T x){
		for(int i=0; i<n; i++){
			if(*K[i]==x) return i;
		}
		return -1;
	}
	/*void selectionSort(T** k){
		int indicemin;
		for(int i=0; i<n-1; i++){
			indicemin=i;
			for(int j=i+1; j<n; j++){
				if(*k[j]<*k[indicemin]){
					T aux;
					indicemin=j;
					aux=*k[indicemin];
					*k[indicemin]=*k[i];
					*k[i] = aux;
				}
			}
		}
	}*/
	void ordina(){
		for(int i=1; i<n; i++){
			int j = i-1;
			while(j>=0 && *K[j] > *K[j+1]){
				T tmp = *K[j+1];
				*K[j+1] = *K[j];
				*K[j] = tmp;
				j--;
			}
		}
	}
public:
	LGrafo(int len){
		this->len=len;
		n = m = backedge = 0;
		K=new T*[len];
		for(int i=0; i<len; i++) K[i]=NULL;
		adj=new Lista*[len];
		for(int i=0; i<len; i++) adj[i]=new Lista();
		c=new int[len];
		d=new int[len];
		in=new int[len];
		f=new int[len];
	}
	LGrafo<T>* addNodo(T val){
		if(n==len) return this;
		if(trovaIndice(val) != -1) return this;
		K[n]=new T(val);
		n++;
		ordina();
		return this;
	}
	LGrafo<T>* addArco(T x, T y){
		int i=trovaIndice(x);
		int j=trovaIndice(y);
		if(i<0 || j<0) return this;
		if(!adj[i]->search(j)){
			adj[i]->insert(j);
		}
		m++;
		//return this;
	}
	void stampa(ofstream& out){
		for(int i=0; i<n; i++){
			out << "(" << *K[i];
			adj[i]->reset();
			while(adj[i]->hasNext()){
				int indice=adj[i]->next();
				out << "," << *K[indice];
			}
			out<<") ";
		}
		out << endl;
	}
};

void soluzione(ifstream& in, ofstream& out) {
	int n; in >> n;
	int m; in >> m;
	string tipo; in >> tipo;
	char c;
	if (tipo == "char") {
		LGrafo<char>* g = new LGrafo<char>(n);
		char val;
		char n1, n2;
		for (int i = 0; i < n; i++) {
			in >> val;		
			g->addNodo(val);
		}
		for (int i = 0; i < m; i++) {
			in >> c;
			in >> n1;
			//in >> c;
			in >> n2;
			in >> c;
			g->addArco(n1, n2);
			
		}
		
		g->stampa(out);
	}
	else {
		LGrafo<double>* g = new LGrafo<double>(n);
		double val;
		double n1, n2;
		for (int i = 0; i < n; i++) {
			in >> val;
			g->addNodo(val);		
		}
		for (int i = 0; i < m; i++) {
			in >> c;
			in >> n1;
			//in >> c;
			in >> n2;
			in >> c;
			g->addArco(n1, n2);
		
		}
		g->stampa(out);
	}
}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");
	for(int i=0; i<100; i++)
		soluzione(input,output);
}















