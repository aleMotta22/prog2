#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* left,*right,*parent;
	T key;
	int altezza;
public:
	Nodo(T key){
		this->key=key;
		left=right=parent=NULL;
		altezza=0;
	}	
	void setLeft(Nodo<T>* left){this->left=left;}
	void setRight(Nodo<T>* right){this->right=right;}
	void setParent(Nodo<T>* parent){this->parent=parent;}
	void setKey(T key){this->key=key;}
	void setAltezza(int altezza){this->altezza=altezza;}
	Nodo<T>* getLeft(){ return left;}
	Nodo<T>* getRight(){ return right;}
	Nodo<T>* getParent(){ return parent;}
	T getKey(){return key;}
	int getAltezza(){ return altezza; }
};

template<class T> class Albero{
private:
	Nodo<T>* root;
	int n;
	int *h;
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
		else  p->setRight(v);
		if(v) v->setParent(p);
	}
	void _preorder(Nodo<T>* r){
		if(r){
			h[r->getAltezza()]++;
			_preorder(r->getLeft());
			_preorder(r->getRight());
		}
	}
	int trovaAltezza(){
		int i=0;
		while(h[i])
			i++;
		return i;
	}
	int liv(Nodo<T>* p){
		Nodo<T>* tmp=root;
		T val=p->getKey();
		while(tmp && tmp->getKey()!=val){
			if(val>tmp->getKey())
				tmp=tmp->getRight();
			else
				tmp=tmp->getLeft();
		}
			
		return tmp->getAltezza();	
	}
	void resetH(Nodo<T>* r, int i){
		if(r){
			r->setAltezza(liv(r));
			resetH(r->getLeft(), i);
			resetH(r->getRight(), i);
		}
	}
public:
	Albero(){
		root=NULL;
		n=0;
		h=new int[n];
	}
	Albero<T>* insert(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		if(!root) root=newn;
		else{
			Nodo<T>* tmp=root;
			Nodo<T>* p;
			int i=0;
			while(tmp){
				p=tmp;
				if(val>tmp->getKey())
					tmp=tmp->getRight();
				else
					tmp=tmp->getLeft();
				newn->setAltezza(++i);		
			}
			newn->setParent(p);
			if(val>p->getKey())
				p->setRight(newn);
			else
				p->setLeft(newn);		
		}
		n++;
		return this;
	}
	Albero<T>* cancella(T val){
		Nodo<T>* x=search(val);
		if(!x->getRight()) trapianta(x,x->getLeft());
		else if(!x->getLeft()) trapianta(x,x->getRight());
		else{
			Nodo<T>* y=min(x->getRight());
			if(y->getParent()!=x){
				trapianta(y,y->getRight());
				y->setRight(x->getRight());
				(y->getRight())->setParent(y);
			}
			trapianta(x,y);
			y->setLeft(x->getLeft());
			(y->getLeft())->setParent(y);
		}
		delete x;
		return this;
	}
	void preorder(){
		for(int i=0; i<n; i++)
			h[i]=0;
		_preorder(root);
		int i=-1;
		resetH(root, i);
		int k=trovaAltezza();
		cout<<k;
		for(int i=0; i<k; i++){
			cout<<" "<< h[i]; 
		}
		cout<<endl;
	}
};

void soluzione(ifstream& in, ofstream& out){
	
}

int main(){
	Albero<int>* a=new Albero<int>();
	a->insert(4)->insert(32)->insert(9)->insert(1)->insert(8);
	a->preorder();
}
