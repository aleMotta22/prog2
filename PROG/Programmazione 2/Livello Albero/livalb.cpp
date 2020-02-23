#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
	private:
		Nodo<T>* padre;
		Nodo<T>* left;
		Nodo<T>* right;
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
		
		Nodo<T>* _search(Nodo<T>* r,T val){
			if(!r) return NULL; //albero vuoto
			if(r->getKey()==val) return r; //l'elemento che cerchiamo è la root
			if(val>r->getKey())
				return _search(r->getRight(), val); //se l'elemento che cerchiamo è maggiore di r cerchiamo nel sottoalbero
			return _search(r->getLeft(), val);	    //destro, altrimenti nel sottoalbero sinistro
		}
		Nodo<T>* _min(Nodo<T>* r){
			if(!r || !r->getLeft()) return r; //se r non esiste oppure r è il minimo del suo sottoalbero ritorniamo r
			return _min(r->getLeft());// che sarà un nodo o null, altrimenti richiamiamo la funzione nel sottoalbero sinistro
		}
		void trapianta(Nodo<T>* n1, Nodo<T>* n2){
			Nodo<T>* p= n1->getPadre();
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
				if(val<=tmp->getKey())
					tmp=tmp->getLeft();
				else
					tmp=tmp->getRight();
			}
			newn->setPadre(p);
			if(val<=p->getKey())
				p->setLeft(newn);
			else
				p->setRight(newn);	
		}
	}
	void search(T val){
		return (_search(root,val))!=NULL;
	}
	T min(){
		Nodo<T>* tmp=_min(root);
		if(tmp) return tmp->getKey();
		return NULL;
	}
	void cancella(T val){
		Nodo<T>* tmp=_search(root,val);
		if(!tmp->getLeft())	trapianta(tmp,tmp->getRight());			//caso 1
		else if(!tmp->getRight()) trapianta(tmp,tmp->getLeft());	//caso 2
		else{														//caso 3
			Nodo<T>* y=_min(tmp->getRight()); //successore
			if(y->getPadre()!=tmp){
				trapianta(y,y->getRight());
				y->setRight(tmp->getRight());
				y->getRight()->setPadre(y);
			}
			trapianta(tmp,y);
				y->setLeft(tmp->getLeft());
				y->getLeft()->setPadre(y);
			
		}
		delete tmp;
	}
	int livello(T val){
		Nodo<T>* tmp=root;
		int liv=0;
		while (tmp && (val!=tmp->getKey())){
			if (val < tmp->getKey()) tmp=tmp->getLeft();
 			else tmp=tmp->getRight();
 			liv++;
 		}
 		return liv;
	}
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	int m; in>>m;
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
		for(int i=0; i<m; i++){
			in>>val;
			out << a->livello(val) << " ";
		}
		out<<endl;
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
		for(int i=0; i<m; i++){
			in>>val;
			out << a->livello(val) << " ";
		}
		out<<endl;
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
