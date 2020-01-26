#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* padre, *left, *right;
	T key;
public:
	Nodo(T val){
		padre=left=right=NULL;
		key=val;
	}
	void setPadre(Nodo<T>* p){ padre=p; }
	void setLeft(Nodo<T>* l){ left=l; }
	void setRight(Nodo<T>* r){ right=r; }
	void setKey(T val){ key=val; }
	Nodo<T>* getPadre(){ return padre; }
	Nodo<T>* getLeft(){ return left; }
	Nodo<T>* getRight(){ return right; }
	T getKey(){ return key; }
};

template<class T> class Albero{
private:
	Nodo<T>* root;
	Nodo<T>* search(T val){
		Nodo<T>* tmp=root;
		while(tmp && tmp->getKey()!=val){
			if(val>tmp->getKey())
				tmp=tmp->getRight();
			else
				tmp=tmp->getLeft();	
		}
		return tmp;
	}
	Nodo<T>* min(Nodo<T>* r){
		while(r->getLeft())
			r=r->getLeft();
		return r;	
	}
	void trapianta(Nodo<T>* u, Nodo<T>* v){
		Nodo<T>* p=u->getPadre();
		if(!p) root=v;
		else if(u==p->getLeft()) p->setLeft(v);
		else p->setRight(v);
		if(v) v->setPadre(p);
	}
	T _peso(Nodo<T>* p, T& val){
		if(p){
			_peso(p->getLeft(), val);
			val+=p->getKey();
			_peso(p->getRight(), val);
		}
		return val;
	}
public:
	Albero(){ root=NULL; }
	void inserimento(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		if(!root) root=newn;
		else{
			Nodo<T>* tmp=root;
			Nodo<T>* p;
			while(tmp){
				p=tmp;
				if(val>tmp->getKey())
					tmp=tmp->getRight();
				else
					tmp=tmp->getLeft();	
			}
			newn->setPadre(p);
			if(val>p->getKey())
				p->setRight(newn);
			else
				p->setLeft(newn);	
		}
	}
	void cancella(T val){
		Nodo<T>* x=search(val);
		if(!x->getLeft()) trapianta(x,x->getRight());
		else if(!x->getRight()) trapianta(x, x->getLeft());
		else{
			Nodo<T>* y=min(x->getRight());
			if(y->getPadre()!=x){
				trapianta(y,y->getRight());
				y->setRight(x->getRight());
				(y->getRight())->setPadre(y);
			}
			trapianta(x,y);
			y->setLeft(x->getLeft());
			(y->getLeft())->setPadre(y);
		}
		delete x;
	}
	T peso(T x, T& val){
		Nodo<T>* tmp=search(x);
		return _peso(tmp, val);
	}
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	char c;
	if(tipo=="int"){
		Albero<int>* a=new Albero<int>();
		int val;
		int key;
		for(int i=0; i<n; i++){
			in>>c;
			if(c=='i'){
				in>>c>>c>>c;
				in>>val;
				a->inserimento(val);
			}
			else{
				in>>c>>c>>c>>c;
				in>>val;
				a->cancella(val);
			}
		}
		in>>key;
		int k=0;
		out << a->peso(key, k) << endl;
	}
	if(tipo=="double"){
		Albero<double>* a=new Albero<double>();
		double val;
		double key;
		for(int i=0; i<n; i++){
			in>>c;
			if(c=='i'){
				in>>c>>c>>c;
				in>>val;
				a->inserimento(val);
			}
			else{
				in>>c>>c>>c>>c;
				in>>val;
				a->cancella(val);
			}
		}
		in>>key;
		double k=0;
		out << a->peso(key, k) << endl;
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
