#include<iostream>
#define W 0
#define G 1
#define B 2

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* succ,* prev,* left,* right,* parent;
	T key;
public:
	Nodo(T key){
		this->key=key;
		succ=prev=left=right=parent=NULL;
	}
	void setSucc(Nodo<T>* succ){ this->succ=succ; }
	void setPrev(Nodo<T>* prev){ this->prev=prev; }
	void setLeft(Nodo<T>* left){ this->left=left; }
	void setRight(Nodo<T>* right){ this->right=right; }
	void setParent(Nodo<T>* parent){ this->parent=parent; }
	void setKey(T key){ this->key=key; }
	Nodo<T>* getSucc(){ return succ; } 
	Nodo<T>* getPrev(){ return prev; } 
	Nodo<T>* getLeft(){ return left; } 
	Nodo<T>* getRight(){ return right; } 
	Nodo<T>* getParent(){ return parent; }
	T getKey(){ return key; } 
};
template<class T> class Coda{
private:
	Nodo<T>* testa,* fine;
public:
	Coda(){ testa=fine=NULL; }
	Coda<T>* insert(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		if(!testa) testa=fine=newn;
		else{
			fine->setSucc(newn);
			fine=newn;
		}
		return this;
	}
	Coda<T>* cancella(){
		if(testa){
			Nodo<T>* tmp=testa;
			testa=testa->getSucc();
			delete tmp;
		}
		return this;
	}
	void stampa(){
		Nodo<T>* tmp=testa;
		while(tmp){
			cout << tmp->getKey() << " ";
			tmp=tmp->getSucc();
		}
		cout << endl;
	}
};
template<class T> class Pila{
private:
	Nodo<T>* testa;
public:
	Pila(){ testa=NULL; }
	Pila<T>* push(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		newn->setSucc(testa);
		testa=newn;
		return this;
	}	
	Pila<T>* pop(){
		if(testa){
			Nodo<T>* tmp=testa;
			testa=testa->getSucc();
			delete tmp;
		}
		return this;
	}
	void stampa(){
		Nodo<T>* tmp=testa;
		while(tmp){
			cout << tmp->getKey() << " ";
			tmp=tmp->getSucc();
		}
		cout << endl;
	}
};
template<typename T> class Lista{
private:
	Nodo<T>* testa,* current;
public:
	Lista(){ testa=current=NULL; }
	Lista<T>* insert(T val){
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
		return this;
	}
	Nodo<T>* search(T val){
		Nodo<T>* tmp=testa;
		while(tmp && tmp->getKey()!=val)
			tmp=tmp->getSucc();
		return tmp;	
	}
	Lista<T>* cancella(T val){
		Nodo<T>* p=search(val);
		if(p){
			if(p==testa){
				testa=testa->getSucc();
				delete p;
			}
			else{
				Nodo<T>* tmp=testa;
				while(tmp->getSucc() && tmp->getSucc()!=p)
					tmp=tmp->getSucc();
				tmp->setSucc(p->getSucc());
				delete p;	
			}
		}
		return this;
	}
	void reset(){ current=testa; }
	int hasNext(){ return current!=NULL; }
	T next(){
		if(hasNext()){
			Nodo<T>* tmp=current;
			current=current->getSucc();
			return tmp->getKey();
		}
		return -1;
	}
	/*void stampa(){
		reset();
		while(hasNext())
			cout << next()->getKey() << " ";
		cout << endl;	
	}*/
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
		Nodo<T>* p=u->getParent();
		if(!p) root=v;
		else if(p->getLeft()==u) p->setLeft(v);
		else p->setRight(v);
		if(v) v->setParent(p);
	}
	void _preorder(Nodo<T>* r){
		if(r){
			cout << r->getKey() << " ";
			_preorder(r->getLeft());
			_preorder(r->getRight());
		}
	}
	void _inorder(Nodo<T>* r){
		if(r){
			_inorder(r->getLeft());
			cout << r->getKey() << " ";
			_inorder(r->getRight());
		}
	}
	void _postorder(Nodo<T>* r){
		if(r){
			_postorder(r->getLeft());
			_postorder(r->getRight());
			cout << r->getKey() << " ";
		}
	}
public:
	Albero(){ root=NULL; }
	Albero<T>* insert(T val){
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
			newn->setParent(p);
			if(val>p->getKey())
				p->setRight(newn);
			else
				p->setLeft(newn);	
		}
		return this;
	}
	void cancella(T val){
		Nodo<T>* x=search(val);
		if(!x->getLeft()) trapianta(x,x->getRight());
		else if(!x->getRight()) trapianta(x,x->getLeft());
		else{
			Nodo<T>* y=min(x->getRight());
			if(y->getParent()!=x){
				trapianta(y,y->getRight());
				y->setRight(x->getRight());
				y->getRight()->setParent(y);
			}
			trapianta(x,y);
			y->setLeft(x->getLeft());
			y->getLeft()->setParent(y);
		}
		delete x;
	}
	void preorder(){
		_preorder(root);
		cout << endl;
	}
	void inorder(){
		_inorder(root);
		cout << endl;
	}
	void postorder(){
		_postorder(root);
		cout << endl;
	}
};
template<class T> class LGrafo{
private:
	T** K;
	Lista<int>** adj;
	int len,n,m;
	int trovaIndice(T x){
		for(int i=0; i<n; i++){
			if(*K[i]==x) return i;
		}
		return -1;
	}
	void ordina(){		//selectionsort
		for(int i=0; i<n-1; i++){
			int min=i;
			for(int j=i+1; j<n; j++){
				if(*K[j]<*K[min])
					min=j;
			}
			T aux = *K[i];
			*K[i] = *K[min];
			*K[min] = aux;
		}
	}
public:
	LGrafo(int len){
		this->len=len;
		n=m=0;
		K=new T*[len];
		for(int i=0; i<len; i++) K[i]=NULL;
		adj=new Lista<int>*[len];
		for(int i=0; i<len; i++) adj[i]=new Lista<int>;
	}
	void addNodo(T val){
		if(n==len) return;
		if(trovaIndice(val)!=-1) return;
		K[n]=new T(val);
		n++;
		ordina();
	}
	void addArco(T x,T y){
		int i=trovaIndice(x);
		int j=trovaIndice(y);
		if(i<0 || j<0) return;
		if(!adj[i]->search(j)){
			adj[i]->insert(j);
			m++;
		}
	}
	void stampa(){
		for(int i=0; i<n; i++){
			cout << "Nodo " << i << ":" << *K[i];
			adj[i]->reset();
			while(adj[i]->hasNext()){
				int indice=adj[i]->next();
				cout << "->" << *K[indice];
			}
			cout << endl;
		}
	}
};
template<class T> class MGrafo{
private:
	T** K;
	int** M;
	int n,m,len;
	int trovaIndice(T x){
		for(int i=0; i<n; i++){
			if(*K[i]==x) return i;
		}
		return -1;
	}
	void ordina(){
		for(int i=0; i<n-1; i++){
			int min=i;
			for(int j=i+1; j<n; j++)
				if(*K[j]<*K[min]) min=j;
			T aux=*K[i];
			*K[i]=*K[min];
			*K[min]=aux;	
		}
	}
public:
	MGrafo(int len){
		this->len=len;
		n=m=0;
		K=new T*[len];
		for(int i=0; i<len; i++) K[i]=NULL;
		M=new int*[len];
		for(int i=0; i<len; i++){
			M[i]=new int[len];
			for(int j=0; j<len; j++)
				M[i][j]=0;
		}
	}
	void addNodo(T val){
		if(n==len) return;
		if(trovaIndice(val)!=-1) return;
		K[n]=new T(val);
		n++;
		ordina();
	}
	void addArco(T x, T y){
		int i=trovaIndice(x);
		int j=trovaIndice(y);
		if(i<0 || j<0) return;
		if(!M[i][j]){
			M[i][j]=1;
			m++;
		}
	}
	void stampa(){
		for(int i=0; i<n; i++){
			cout << "(" << *K[i];
			for(int j=0; j<n; j++){
				if(M[i][j]){
					cout << "," << *K[j];
				}
			}
			cout << ") ";
		}
		cout << endl;
	}
};
int main(){
	
}
