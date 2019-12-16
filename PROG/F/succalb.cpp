#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* padre,* left,* right;
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
	int n;
	Nodo<T>* _search(Nodo<T>* r, T val){
		if(!r) return NULL;
		if(r->getKey()==val) return r;
		if(val>r->getKey()) return _search(r->getRight(),val);
		return _search(r->getLeft(),val);
	}
	Nodo<T>* _rmin(Nodo<T>* r) {			//restituisce il nodo minore a partire dal nodo passato come parametro
		if (!r || !r->getLeft()) return r;
		return _rmin(r->getLeft());
	}
	Nodo<T>* _successore(Nodo<T>* y) {
		if (!y) return NULL;
		T x = y->getKey();
		if (y->getRight()) {
			y = _rmin(y->getRight());
			return y;
		}
		else {
			do y = y->getPadre();
			while (y && y->getKey() < x);
			if (y) return y;
			return NULL;
		}
	}
	void _cancella(Nodo<T>* x, T val){
		Nodo<T>* tmp=_search(x,val);
		if(tmp){
			if(tmp->getLeft() && tmp->getRight()){
				Nodo<T>* s=_successore(tmp);
				tmp->setKey(s->getKey());
				_cancella(s,s->getKey());
			}
			else{
				Nodo<T>* figlio=tmp->getLeft();
				if(!figlio)
					figlio=tmp->getRight();
				Nodo<T>* p=tmp->getPadre();
				if(p){
					if(x->getKey()<p->getKey())
						p->setLeft(figlio);
					else
						p->setRight(figlio);	
				}
				else
					root=figlio;
				if(figlio){
					figlio->setPadre(p);
				}	
				n--;
			}
		}
	}
	void _postorder(Nodo<T>* r) {
        if(r) {
            _postorder(r->getLeft());
            _postorder(r->getRight());
            cout << r->getKey() << " ";
        }
    }
public:
	Albero(){ root=NULL; n=0; }

	int search(T val){ return(_search(root,val)!=NULL); } //cerca un nodo dell'albero
	
	void inserimento(T val){
		Nodo<T>* newn=new Nodo<T>(val);
		if(!root)
			root=newn;
		else{
			Nodo<T>* tmp=root;
			Nodo<T>* p;
			while(tmp){
				p=tmp;
				if(val<=tmp->getKey())
					tmp=tmp->getLeft();
				else
					tmp=tmp->getRight();
			}
			newn->setPadre(p);
			if(val>p->getKey())
				p->setRight(newn);
			else
				p->setLeft(newn);		
		}
	}
	T min() {							//restituisce il minimo dell'albero
		Nodo<T>* y = _rmin(root);
		return y ? y->getKey() : NULL;
	}
	void cancella(T x){
		Nodo<T>* tmp=_search(root, x);
		if(tmp) _cancella(tmp,x);
	}
	T successore(T x) {
        Nodo<T>* y = _search(root, x);
        y = _successore(y);
        if(y) return y->getKey();
	}
	void postorder(){
		_postorder(root);
		cout<<endl;
	}
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	int chiavi; in>>chiavi;
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
		for(int j=0; j<chiavi; j++){
			in>>key;
			if(a->successore(key))
				out << a->successore(key) << " ";
			else
				out<<-1<<" ";
		}
		out << endl;
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
		for(int j=0; j<chiavi; j++){
			in>>key;
			if(a->successore(key))
				out << a->successore(key) << " ";
			else
				out<<-1<<" ";
		}
		out << endl;
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
	
	
}
