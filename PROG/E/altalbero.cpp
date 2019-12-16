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
			Nodo<T>* tmp=r;
			while(tmp->getLeft())
				tmp=tmp->getLeft();
			return tmp;	
		}
		void trapianta(Nodo<T>* u, Nodo<T>* v){
			Nodo<T>* p=u->getPadre();
			if(p==NULL) root=v;
			else if(u==p->getLeft()) p->setLeft(v);
			else p->setRight(v);
			if(v) v->setPadre(p);
		}
    int _altezza(Nodo<T>* r){
			if(!r) return 0;
			int sin=_altezza(r->getLeft());
			int des=_altezza(r->getRight());
			return 1+max(sin,des);
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
			Nodo<T>* tmp=search(val);
			if(!(tmp->getLeft())) trapianta(tmp, tmp->getRight());
			else if(!(tmp->getRight())) trapianta(tmp, tmp->getLeft());
			else{
				Nodo<T>* succ=min(tmp->getRight());
				if(succ->getPadre() != tmp){
					trapianta(succ,succ->getRight());
					succ->setRight(tmp->getRight());
					(succ->getRight())->setPadre(succ);
				}
				trapianta(tmp,succ);
				succ->setLeft(tmp->getLeft());
				(succ->getLeft())->setPadre(succ);
			}
		}
		int altezza(ofstream& out){
			out<< _altezza(root) << endl;
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
		a->altezza(out);
	}
	if(tipo=="double"){
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
		a->altezza(out);
	}
}
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
