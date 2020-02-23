#include<iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo{
private:
	Nodo<T>* left,* right,* parent;
	T key;
	int molt;
public:
	Nodo(T key){
		this->key=key;
		left=right=parent=NULL;
		molt=1;
	}
	void setLeft(Nodo<T>* left){ this->left=left; }
	void setRight(Nodo<T>* right){ this->right=right; }
	void setParent(Nodo<T>* parent){ this->parent=parent; }
	void setMolt(int molt){this->molt=molt;}
	Nodo<T>* getLeft(){ return left; }
	Nodo<T>* getRight(){ return right; }
	Nodo<T>* getParent(){ return parent; }
	T getKey(){ return key; }
	int getMolt(){ return molt; }
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
	void _preorder(Nodo<T>* r, ofstream& out){
		if(r){
			if(r->getMolt()>1){
				for(int i=0; i<r->getMolt(); i++)
					out<<r->getKey()<<" ";
			}
			else{
				out << r->getKey() << " ";
			}
			_preorder(r->getLeft(),out);
			_preorder(r->getRight(),out);
		}
	}
	void _inorder(Nodo<T>* r, ofstream& out){
		if(r){
			_inorder(r->getLeft(),out);
			if(r->getMolt()>1){
				for(int i=0; i<r->getMolt(); i++)
					out<<r->getKey()<<" ";
			}
			else{
				out << r->getKey() << " ";
			}
			_inorder(r->getRight(),out);
		}
	}
	void _postorder(Nodo<T>* r, ofstream& out){
		if(r){
			_postorder(r->getLeft() ,out);
			_postorder(r->getRight(), out);
			if(r->getMolt()>1){
				for(int i=0; i<r->getMolt(); i++)
					out<<r->getKey()<<" ";
			}
			else{
				out << r->getKey() << " ";
			}
		}
	}
public:
	Albero(){ root=NULL; }
	void insert(T val){
		Nodo<T>* tmp=search(val);
		if(tmp){
			tmp->setMolt(tmp->getMolt()+1);
		}
		else{
			Nodo<T>* newn=new Nodo<T>(val);
			if(!root)
				root=newn;
			else{
				tmp=root;
				Nodo<T>* p;
				while(tmp && tmp->getKey()!=val){
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
		}
	}
	void cancella(T val){
		Nodo<T>* x=search(val);
		if(x->getMolt()>1)
			x->setMolt(x->getMolt()-1);
		else{
			if(!x->getRight()) trapianta(x,x->getLeft());
			else if(!x->getLeft()) trapianta(x,x->getRight());
			else{
				Nodo<T>* y=min(x->getRight());
				if(y->getParent()!=x){
					trapianta(y, y->getRight());
					y->setRight(x->getRight());
					(y->getRight())->setParent(y);
				}
				trapianta(x,y);
				y->setLeft(x->getLeft());
				(y->getLeft())->setParent(y);
			}
			delete x;
		}	
	}
	void preorder(ofstream& out){
		_preorder(root, out);
		out<< endl;
	}
	void inorder(ofstream& out){
		_inorder(root, out);
		out<< endl;
	}
	void postorder(ofstream& out){
		_postorder(root, out);
		out<< endl;
	}
	void stampa(string visita, ofstream& out){
		if(visita=="preorder")
			preorder(out);
		if(visita=="inorder")
			inorder(out);
		if(visita=="postorder")
			postorder(out);		
	}
};
void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	string visita; in>>visita;
	char c;
	if(tipo=="char"){
		Albero<char>* a=new Albero<char>();
		char val;
		for(int i=0; i<n; i++){
			in>>c;
			if(c=='i'){
				in>>c>>c>>c;
				in>>val;
				a->insert(val);
			}
			else{
				in>>c>>c>>c>>c;
				in>>val;
				a->cancella(val);
			}
		}
		a->stampa(visita, out);
	}
	else{
		Albero<double>* a=new Albero<double>();
		double val;
		for(int i=0; i<n; i++){
			in>>c;
			if(c=='i'){
				in>>c>>c>>c;
				in>>val;
				a->insert(val);
			}
			else{
				in>>c>>c>>c>>c;
				in>>val;
				a->cancella(val);
			}
		}
		a->stampa(visita, out);
	}
}
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in,out);
}
