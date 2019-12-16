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
		int n;
		
		Nodo<T>* search(T val){
			Nodo<T>* tmp=root;
			while(tmp && tmp->getKey()!=val){
				if(val<=tmp->getKey())
					tmp=tmp->getLeft();
				else
					tmp=tmp->getRight();	
			}
			return tmp;
		}
		void trapianta(Nodo<T>* n1, Nodo<T>* n2){
			Nodo<T>* p=n1->getPadre();
			if(p==NULL) root=n2;
			else if(n1==p->getLeft()) p->setLeft(n2);
			else p->setRight(n2);
			
			if(n2) n2->setPadre(p); 
		}
		
	public:
		Albero(){
			root=NULL;
			n=0;
		}
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
				if(p->getKey()>val)
					p->setLeft(newn);
				else
					p->setRight(newn);	
			}
		}
		Nodo<T>* min(Nodo<T>* r){
			Nodo<T>* tmp=r;
			while(tmp->getLeft()){
				tmp=tmp->getLeft();
			}
			return tmp;
		}
		Nodo<T>* max(Nodo<T>* r){
			Nodo<T>* tmp=r;
			while(tmp->getRight()){
				tmp=tmp->getRight();
			}
			return tmp;
		}
		void cancella(T val){
			Nodo<T>* tmp=search(val);
			if(!(tmp->getLeft())) trapianta(tmp,tmp->getRight());
			else if(!(tmp->getRight())) trapianta(tmp,tmp->getLeft());
			else{
				Nodo<T>* s=min(tmp->getRight());
				if(s->getPadre()!=tmp){
					trapianta(s,s->getRight());
					s->setRight(tmp->getRight());
					(s->getRight())->setPadre(s);
				}
				trapianta(tmp,s);
				s->setLeft(tmp->getLeft());
				(s->getLeft())->setPadre(s);
			}
		}
		T predecessore(T val){
			Nodo<T>* tmp=search(val);
			if(tmp){
				if(tmp==min(root))
					return -1;
				if(tmp->getLeft()){
					Nodo<T>* n=max(tmp->getLeft());
					return n->getKey();
			}
				else{
					Nodo<T>* papa=tmp->getPadre();
					while(papa && papa->getLeft()==tmp){
						tmp=papa;
						papa=papa->getPadre();
					}
					return papa->getKey();
				}
			}
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
			out << a->predecessore(key) << " ";
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
			out << a->predecessore(key) << " ";
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
