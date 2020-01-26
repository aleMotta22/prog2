#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* left,* right,* padre;
	T key;
public:
	Nodo(T val){ left=right=padre=NULL; key=val;}
	Nodo<T>* getLeft(){ return left;}
	Nodo<T>* getRight(){ return right;}
	Nodo<T>* getPadre(){ return padre;}
	T getKey(){ return key; }
	void setPadre(Nodo<T>* p){ padre=p; }
	void setLeft(Nodo<T>* l){ left=l; }
	void setRight(Nodo<T>* r){ right=r; }
	void setKey(T val){ key=val; }
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
	void trapianta(Nodo<T>* u,Nodo<T>* v){
		Nodo<T>* p=u->getPadre();
		if(!p) root=v;
		else if(p->getLeft()==u) p->setLeft(v);
		else p->setRight(v);
		if(v) v->setPadre(p);
	}
	int _contafoglie(Nodo<T>* p, int& i){
		if(p){
			if(!p->getLeft() && !p->getRight())
				i++;
			_contafoglie(p->getLeft(), i);
			_contafoglie(p->getRight(), i);
		}
		return i;
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
		if(!x->getRight()) trapianta(x,x->getLeft());
		else if(!x->getLeft()) trapianta(x,x->getRight());
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
	}
	int contafoglie(){
		int i=0;
		return _contafoglie(root, i);
	}	
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	char c;
	if(tipo=="int"){
		Albero<int>* a=new Albero<int>();
		int val;
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
		out<< a->contafoglie() << endl;
	}
	else if(tipo=="double"){
		Albero<double>* a=new Albero<double>();
		double val;
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
		out<< a->contafoglie() << endl;
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}

