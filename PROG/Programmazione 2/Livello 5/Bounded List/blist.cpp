#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* succ;
	T key;
public:
	Nodo(T key){
		this->key=key;
		succ=NULL;
	}
	void setSucc(Nodo<T>* succ){ this->succ=succ;}
	Nodo<T>* getSucc(){ return succ; }
	T getKey(){ return key; }
};
template<class T> class Lista{
private:
	Nodo<T>* testa,* current;
	int n;
	Nodo<T>* search(T val){
		Nodo<T>* tmp=testa;
		while(tmp && tmp->getKey()!=val)
			tmp=tmp->getSucc();
		return tmp;	
	}
public:
	Lista(){
	 testa = current= NULL;
	 n=0;
	}
	void insert(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		if(!testa) testa=newn;
		else if(testa->getKey()>val){
			newn->setSucc(testa);
			testa=newn;
		}
		else{
			Nodo<T>* tmp=testa;
			while(tmp->getSucc() && tmp->getSucc()->getKey()<=val)
				tmp=tmp->getSucc();
			newn->setSucc(tmp->getSucc());
			tmp->setSucc(newn);
		}
		n++;
	}
	void cancella(T val){
		Nodo<T>* tmp=search(val);
		if(tmp){
			Nodo<T>* t=testa;
			if(tmp==t)
				testa=testa->getSucc();
			else{
				while(t->getSucc() && t->getSucc()->getKey()!=val)
					t=t->getSucc();
				t->setSucc(tmp->getSucc());
			}
			delete tmp;
			n--;
		}
	}
	void reset(){ current=testa; }
	int hasNext(){ return current!=NULL; }
	Nodo<T>* next(){
		if(hasNext()){
			Nodo<T>* tmp=current;
			current=current->getSucc();
			return tmp;
		}
		return NULL;
	}
	void stampa(ofstream& out){
		reset();
		while(hasNext()){
			out<<next()->getKey() << " ";
		}
		//cout<<endl;
	}
	int getSize(){ return n; }
};

template<class T> class LNodo{
private:
	LNodo<T>* succ;
	Lista<T>* lkey;
public:
	LNodo(Lista<T>* lkey){
		this->lkey=lkey;
		succ=NULL;
	}
	LNodo<T>* getSucc(){ return succ; }
	Lista<T>* getLKey(){ return lkey; }
	void setSucc(LNodo<T>* succ){ this->succ=succ; }
	int size(){ return lkey->getSize(); }
};

template<class T> class Bounded{
private:
	LNodo<T>* testa,* current;
	int k;
public:
	Bounded(int k){
		this->k=k;
		testa=NULL;
	}
	void insert(T val){
		if(testa && testa->size()<k){
			testa->getLKey()->insert(val);
		}
		else{
			Lista<T>* tmp=new Lista<T>();
			tmp->insert(val);
			LNodo<T>* newn = new LNodo<T>(tmp);
			newn->setSucc(testa);
			testa=newn;
		}
	}
	void cancella(T val){
		reset();
		while(hasNext()){
			LNodo<T>* tmp=next();
			tmp->getLKey()->cancella(val);
		}
	}
	void reset(){ current=testa; }
	int hasNext(){ return current!=NULL; }
	LNodo<T>* next(){
		if(hasNext()){
			LNodo<T>* tmp=current;
			current=current->getSucc();
			return tmp;
		}
		return NULL;
	}
	void stampa(ofstream& out){
		reset();
		while(hasNext()){
			next()->getLKey()->stampa(out);
		}
		//cout << endl;
	}
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int k; in>>k;
	char c;
	double val;
	Bounded<double>* b=new Bounded<double>(k);
	while(1){
		in>>c;
		if(c=='i'){
			in>>c>>c;
			in>>val;
			b->insert(val);
		}
		else if(c=='c'){
			in>>c>>c>>c;
			in>>val;
			b->cancella(val);
		}
		else break;
	}
	b->stampa(out);
	out<<endl;
}
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
