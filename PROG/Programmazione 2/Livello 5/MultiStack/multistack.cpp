#include<iostream>
#include<fstream>

using namespace std;

template<class T> class PNodo {
private:
	PNodo<T>* succ;
	T key;
public:
	PNodo(T key) {
		this->key = key;
		succ = NULL;
	}
	PNodo<T>* getSucc() { return succ; }
	T getKey() { return key; }
	void setSucc(PNodo<T>* succ) { this->succ = succ; }
	void setKey(T key) { this->key = key; }
};

template<class T> class Pila {
private:
	PNodo<T>* testa=NULL;
	PNodo<T>* current;
public:
	Pila(T val) { push(val); }
	void push(T val) {
		PNodo<T>* newn = new PNodo<T>(val);
		if(testa)
			newn->setSucc(testa);
		testa = newn;
	}
	void pop() {
		if(testa){
			PNodo<T>* tmp = testa;
			testa = testa->getSucc();
			delete tmp;
		}
	}
	void reset(){ current=testa; }
	int hasNext(){ return current!=NULL; }
	T next(){
		if(hasNext()){
			PNodo<T>* tmp=current;
			current=current->getSucc();
			return tmp->getKey();
		}
		return -1;
	}
	void stampa(ofstream& out){
		reset();
		//cout << '(';
		while(hasNext()){
			out << next() << " ";
		}
		//cout << ")" << " ";
	}
};

template<class T> class LNodo {
private:
	LNodo<T>* succ;
	T* key;
public:
	LNodo(T* key) {
		this->key = key;
		succ = NULL;
	}
	LNodo<T>* getSucc() { return succ; }
	T* getKey() { return key; }
	void setSucc(LNodo<T>* succ) { this->succ = succ; }
	void setKey(T* key) { this->key = key; }
};

template<class T> class Lista {
private:
	LNodo<T>* testa,* current;
	LNodo<T>* search(T* val){
		LNodo<T>* tmp=testa;
		while(tmp && tmp->getKey()!=val)
			tmp=tmp->getSucc();
		return tmp;	
	}
public:
	Lista() { testa = current = NULL; }
	void insert(T* val){
		LNodo<T>* nuovo = new LNodo<T>(val);

		if(!testa){
			testa = nuovo;
		}
		else if(*testa->getKey() > *val){
			nuovo->setSucc(testa);
			testa = nuovo;
		}
		else{
			LNodo<T>* tmp = testa;
			
			while(tmp->getSucc() &&  *val >= *(tmp->getSucc())->getKey()){
				tmp = tmp->getSucc();
			}

			nuovo->setSucc(tmp->getSucc());
			tmp->setSucc(nuovo);
		}
	}
	void cancella(T* val){
		LNodo<T>* tmp=search(val);
		if(tmp){
			LNodo<T>* t=testa;
			if(tmp==t){
				testa=testa->getSucc();
			}
			else{
				while(t->getSucc() && t->getSucc()!=tmp)
					t=t->getSucc();
				t->setSucc(tmp->getSucc());	
			}
		}
	}
	void reset() { current = testa; }
	int hasNext() { return current != NULL; }
	T* next() {
		if (hasNext()) {
			LNodo<T>* tmp = current;
			current = current->getSucc();
			return tmp->getKey();
		}
		return NULL;
	}
	void stampa(ofstream& out) {
		reset();
		while (hasNext()) {
			out<<*next()<<" ";
		}
		out << endl;
	}
};

template<class T> class MultiStack {
private:
	Lista< Pila<T> >* l;
public:
	MultiStack() {
		l = new Lista<Pila<T> >();
	}
	void newPush(T val) {
		Pila<T>* p = new Pila<T>(val);
		l->insert(p);
	}
	void push(T val) {
		l->reset();
		Pila<T>* p=l->next();
		p->push(val);
		l->cancella(p);
		l->insert(p);
	}
	void pop(){
		l->reset();
		Pila<T>* p=l->next();
		p->pop();
		p->reset();
		if(p->hasNext()){
			l->cancella(p);
			l->insert(p);
		}
		else	
			l->cancella(p);
	}
	void stampa(ofstream& out) {
		l->reset();
		while(l->hasNext())
			l->next()->stampa(out);
		out<<endl;
	}
};
template<typename T>
bool operator >(Pila<T>& p1, Pila<T>& p2){
	p1.reset();
	p2.reset();
	T x= p1.next();
	T y= p2.next();
	return (x>y);
}
template<typename T>
bool operator >=(Pila<T>& p1, Pila<T>& p2){
	p1.reset();
	p2.reset();
	T x= p1.next();
	T y= p2.next();
	return (x>=y);
}
void soluzione(ifstream& in, ofstream& out){
	string tipo; in>>tipo;
	int n; in>>n;
	char c,dp;
	MultiStack<double>* m=new MultiStack<double>();
	double val;
	for(int i=0; i<n; i++){
		in>>c;
		in>>dp;
		if(c=='n'){
			in>>val;
			m->newPush(val);
		}
		else{
			if(dp==':'){
				in>>val;
				m->push(val);
			}
			else{
				m->pop();
				in>>c;
			}
		}
	}
	m->stampa(out);
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<100; i++)
		soluzione(in, out);
	
}

