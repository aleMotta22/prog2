#include<iostream>
#include<fstream>

using namespace std;

template<class T> class LNodo{
private:
	LNodo<T>* prev,* succ;
	T* key;
public:
	LNodo(T* key){
		this->key=key;
		prev=succ=NULL;
	}
	void setSucc(LNodo<T>* succ){ this->succ=succ; }
	void setPrev(LNodo<T>* prev){ this->prev=prev; }
	void setKey(T key){ this->key=key; }
	LNodo<T>* getPrev(){return prev;}	
	LNodo<T>* getSucc(){return succ;}
	T* getKey(){ return key; }
	
};

template<class T> class Lista{
private:
	LNodo<T>* testa, *current;
	int n;
	
	LNodo<T>* search(T* val){
		LNodo<T>* tmp=testa;
		while(tmp && tmp->getKey()!=val)
			tmp=tmp->getSucc();
		return tmp;	
	}
public:
	Lista(){
		testa=current=NULL;
		n=0;
	}
	Lista<T>* insert(T* val){
		LNodo<T>* newn=new LNodo<T>(val);
		if(!testa) testa=newn;
		else{
			newn->setSucc(testa);
			testa->setPrev(newn);
			testa=newn;
		}
		n++;
		return this;
	}
	Lista<T>* cancella(T* val){
		LNodo<T>* tmp=search(val);
		if(tmp){
			LNodo<T>* p=tmp->getPrev();
			if(p)
				p->setSucc(tmp->getSucc());
			else
				testa=testa->getSucc();
			LNodo<T>* s=tmp->getSucc();
			if(s)
				s->setPrev(tmp->getPrev());
						
			delete tmp;
			n--;
		}
		return this;
	}
	int getSize(){ return n; }
	void reset(){ current=testa; }
	int hasNext() {
        return current!=NULL;
    }
    
    T* next() {
        if(hasNext()) {
            LNodo<T>* x = current;
            current = current->getSucc();
            return x->getKey();
        }
        return NULL;
    }
    void stampa(){
    	reset();
    	while(hasNext()){
    		cout<<next()<<" ";
		}
		cout<<endl;
	}
};
template<class T> class TNodo{
private:
	TNodo<T>* left,* right,* parent;
	T key;
public:
	TNodo(T key){
		this->key=key;
		left=right=parent=NULL;
	}
	void setLeft(TNodo<T>* left){ this->left=left;}
	void setRight(TNodo<T>* right){ this->right=right;}
	void setParent(TNodo<T>* parent){ this->parent=parent;}
	void setKey(T key){ this->key=key; }
	TNodo<T>* getLeft(){ return left; }
	TNodo<T>* getRight(){ return right; }
	TNodo<T>* getParent(){ return parent; }
	T getKey(){ return key; }
};

template<class T> class Albero{
private:
	TNodo<T>* root;
	int n;
	TNodo<T>* min(TNodo<T>* r){
		while(r->getLeft())
			r=r->getLeft();
		return r;	
	}
	void trapianta(TNodo<T>* u, TNodo<T>* v){
		TNodo<T>* p=u->getParent();
		if(!p) root=v;
		else if(p->getLeft()==u) p->setLeft(v);
		else p->setRight(v);
		if(v) v->setParent(p);
	}
	void _preorder(TNodo<T>* r, ofstream& out){
		if(r){
			out<<r->getKey()<<" ";
			_preorder(r->getLeft(), out);
			_preorder(r->getRight(), out);
		}
	}
public:
	Albero(){
		root=NULL;
		n=0;
	}
	Albero<T>* insert(T val){
		TNodo<T>* newn=new TNodo<T>(val);
		if(!root) root=newn;
		else{
			TNodo<T>* tmp=root;
			TNodo<T>* p;
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
		n++;
		return this;
	}
	TNodo<T>* search(T val) {
		TNodo<T>* tmp = root;
		while (tmp && tmp->getKey() != val) {
			if (val > tmp->getKey())
				tmp = tmp->getRight();
			else
				tmp = tmp->getLeft();
		}
		return tmp;
	}
	void cancella(T val){
		TNodo<T>* x=search(val);
		if(!x->getRight()) trapianta(x, x->getLeft());
		else if(!x->getLeft()) trapianta(x, x->getRight());
		else{
			TNodo<T>* y=min(x->getRight());
			if(y->getParent()!=x){
				trapianta(y,y->getRight());
				y->setRight(x->getRight());
				(y->getRight())->setParent(y);
			}
			trapianta(x,y);
			y->setLeft(x->getLeft());
			(y->getLeft())->setParent(y);
		}
		n--;
		delete x;
	}
	void preorder(ofstream& out){
		_preorder(root, out);
		
	}
	int size(){ return n; }
};

template<class T> class LOT{
private:
	Lista< Albero<T> >* l;
	int k;
public:
	LOT(int k){
		this->k=k;
		l=new Lista< Albero<T> >();
	}
	void insert(T x){
		l->reset();
		Albero<T>* a = l->next();
		if(a && a->size()<k)
			a->insert(x);
		else{
			a=new Albero<T>();
			l->insert(a);
			a->insert(x);
		}	
	}
	void cancella(T val) {
		Albero<T>* a;
		l->reset();
		while (l->hasNext()) {
			a = l->next();
			while (a->search(val))
				a->cancella(val);
			if (!a->size())
				l->cancella(a);
		}
	}
	void stampa(ofstream& out){
		l->reset();
		while(l->hasNext()){
			Albero<T>* a=l->next();
			a->preorder(out);	
		}
	}
};

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int k=0;
	double num=0.0;
	string put="";
	for(int i=0; i<100; i++){
		in>>put>>k;
		LOT<double>* l=new LOT<double>(k);
		while(1){
			in>>put;
			if(put[0]=='i'){
				in>>num;
				l->insert(num);
			}
			else if(put[0] =='c'){
				in>>num;
				l->cancella(num);
			}
			else break;
		}
		l->stampa(out);
		out<<endl;
	}
}
