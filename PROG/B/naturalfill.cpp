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
			while(tmp->getLeft()){
				tmp=tmp->getLeft();
			}
			return tmp;
		}
		void trapianta(Nodo<T>* u, Nodo<T>* v){
			Nodo<T>* p = u->getPadre();
			if(!p) root=v;
			else if(p->getLeft()==u) p->setLeft(v);
			else p->setRight(v);
			if(v) v->setPadre(p);
		}
		void _insertvett(Nodo<T>* p, int &i, T vett[]){
			if(p){
				_insertvett(p->getLeft(), i, vett);
				p->setKey(vett[i]);
				i++;
				_insertvett(p->getRight(), i, vett);
			}
		}
		void _postorder(Nodo<T>* p, ofstream& out){
			if(p){
				_postorder(p->getLeft(), out);
				_postorder(p->getRight(), out);
				out<< p->getKey() << " ";
			}
		}
	public:
		Albero(){ root = NULL; }
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
			Nodo<T>* cnodo=search(val);
			if(!(cnodo->getLeft())) trapianta(cnodo, cnodo->getRight());
			else if(!(cnodo->getRight())) trapianta(cnodo, cnodo->getLeft());
			else{
				Nodo<T>* s=min(cnodo->getRight());
				if(s->getPadre()!=cnodo){
					trapianta(s,s->getRight());
					s->setRight(cnodo->getRight());
					(s->getRight())->setPadre(s);
				}
				trapianta(cnodo,s);
				s->setLeft(cnodo->getLeft);
				(s->getLeft())->setPadre(s);
			}
		}
		
		void postorder(ofstream& out){
			_postorder(root, out);
			out<<endl;
		}
		void insertvett(int &i, T vett[]){
			_insertvett(root, i, vett);
		}	
};

void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	if(tipo=="int"){
		Albero<int>* a=new Albero<int>();
		int* vett=new int[n];
		int val;
		for(int i=0; i<n; i++){
			in>>val;
			a->inserimento(val);
		}
		for(int i=0; i<n; i++){
			in>>val;
			vett[i]=val;
		}
		int tmp=0;
		a->insertvett(tmp, vett);
		a->postorder(out);
	}
	if(tipo=="double"){
		Albero<double>* a=new Albero<double>();
		double* vett=new double[n];
		double val;
		for(int i=0; i<n; i++){
			in>>val;
			a->inserimento(val);
		}
		for(int i=0; i<n; i++){
			in>>val;
			vett[i]=val;
		}
		int tmp=0;
		a->insertvett(tmp, vett);
		a->postorder(out);
	}
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
