#include <iostream>
#include<fstream>

using namespace std;

template<class T> class Nodo {
private:
	T key;
	Nodo<T>* succ;
public:
	Nodo(T val) {
		key = val;
		succ = NULL;
	}
	void setSucc(Nodo<T>* t) { succ = t; }
	void setKey(T k) { key = k; }
	T getKey() { return key; }
	Nodo<T>* getSucc() { return succ; }
};

template<class T> class Stack {
private:
	Nodo<T>* testa;
public:
	Stack(){ testa = NULL; }
	void svuotaStack() { testa = NULL; }                
	bool vuoto() { return testa == NULL; }

	Stack<T>* push(T val) {
		Nodo<T>* tmp = new Nodo<T>(val);
		if (testa)
			tmp->setSucc(testa);
		testa = tmp;
		return this;
		}
	T pop() {
		if (testa) {
			Nodo<T>* tmp = testa;
			T val = tmp->getKey();
			testa = testa->getSucc();
			delete tmp;
			return val;
		}
	}
	void stampaP(ofstream &out) {
		Nodo<T>* pnodo = testa;

		if (pnodo == NULL)
			out << "Pila vuota!" << endl;
		while (pnodo) {
			out << pnodo->getKey() << " ";
			pnodo = pnodo->getSucc();
		}
		out << endl;
	}
};

template<class T> class Coda {
private:
	Stack<T>* inizio;
	Stack<T>* fine;
public:
	Coda() {
		inizio = new Stack<T>();
		fine = new Stack<T>();
	}

	void insertQ(T val) {
		inizio->push(val);
	}
	void estrai() {
		while (!(inizio->vuoto())){
			fine->push(inizio->pop());
		}
		fine->pop();
		while(!(fine->vuoto()))
			inizio->push(fine->pop());
	}

	void stampaQ(ofstream& out) {
		while (!(inizio->vuoto())){
			fine->push(inizio->pop());
		}
		fine->stampaP(out);
	}
};

void metodo(ifstream& in, ofstream& out) {
	string tipo; in >> tipo;
	int n; in >> n;
	string tmp;
	char c;
	if (tipo == "int") {
		Coda<int>* Q = new Coda<int>();
		int val;
		for (int i = 0; i < n; i++) {
			in>>c;
			if(c=='i'){
				in>>val;
				Q->insertQ(val);
			}
			else{
				Q->estrai();
				in>>tmp;
			}
		}
		Q->stampaQ(out);
	}
	if (tipo == "double") {
		Coda<double>* Q = new Coda<double>();
		double val;
		for (int i = 0; i < n; i++) {
			in>>c;
			if(c=='i'){
				in>>val;
				Q->insertQ(val);
			}
			else{
				Q->estrai();
				in>>tmp;
			}
		}
		Q->stampaQ(out);
	}
	if (tipo == "char") {
		Coda<char>* Q = new Coda<char>();
		char val;
		for (int i = 0; i < n; i++) {
			in>>c;
			if(c=='i'){
				in>>val;
				Q->insertQ(val);
			}
			else{
				Q->estrai();
				in>>tmp;
			}
		}
		Q->stampaQ(out);
	}
	if (tipo == "bool") {
		Coda<bool>* Q = new Coda<bool>();
		bool val;
		for (int i = 0; i < n; i++) {
			in>>c;
			if(c=='i'){
				in>>val;
				Q->insertQ(val);
			}
			else{
				Q->estrai();
				in>>tmp;
			}
		}
		Q->stampaQ(out);
	}
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	for (int i = 0; i < 100; i++)
		metodo(in, out);
}
