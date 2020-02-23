#include<iostream>
#include<fstream>
using namespace std;

template<typename H>
class Nodo
{
	Nodo<H>* succ;
	H* key;
public:
	Nodo(H* key){
		this->key = key;
		succ = NULL;
	}

	Nodo<H>* getSucc(){return succ;}
	H* getKey(){return key;}
	void setSucc(Nodo<H>* p){succ = p;}
	void setKey(H* val){key = val;}
};

template<typename H>
class Lista
{
	Nodo<H>* testa;
	Nodo<H>* current;
	int n, dim;
public:
	Lista(int dim){
		this->dim = dim;
		testa = current = NULL;
		n = 0;
	}

	void add(H val){
		if(n != dim){
			Nodo<H>* nuovo = new Nodo<H>(new H(val));
			if(!testa){
				testa = nuovo;
				current = testa;
			}
			else{
				current->setSucc(nuovo);
				current = nuovo;
			}
			n++;
		}
	}

	void add(H* val){
		if(n != dim){
			Nodo<H>* nuovo = new Nodo<H>(val);
			if(!testa){
				testa = nuovo;
				current = testa;
			}
			else{
				current->setSucc(nuovo);
				current = nuovo;
			}
			n++;
		}
	}

	int size(){return n;}
	void reset(){current = testa;}
	bool hasNext(){return current!=NULL;}
	H* next(){
		if(hasNext()){
			Nodo<H>* tmp = current;
			current = current->getSucc();
			return tmp->getKey();
		}
		return NULL;
	}

	H search(int index){
		reset();
		int i = 0;
		while(hasNext() && i != index){
			H* aux = next();
			i++;
		}
		if(hasNext())
		return *next();
		return -1;
	}

	void print(ofstream& output){
		reset();
		while(hasNext()){
			output << *next() << " ";
		}
		//cout << endl;
	}
};

template<typename H>
class lmatrix
{
	Lista<Lista<H> >* A, *B, *C; 
	int N,M,P;
	int cont;
public:
	lmatrix(int N, int M, int P){
		this->N = N;
		this->M = M;
		this->P = P;
		cont = 0;
		A = new Lista<Lista<H> >(N);

		for(int i=0; i<N; i++){
			Lista<H>* aux = new Lista<H>(M);
			A->add(aux);
		}

		B = new Lista<Lista<H> >(M);

		for(int i=0; i<M; i++){
			Lista<H>* aux = new Lista<H>(P);
			B->add(aux);
		}

		C = new Lista<Lista<H> >(N);

		for(int i=0; i<N; i++){
			Lista<H>* aux = new Lista<H>(P);
			C->add(aux);
		}

	}

	void add(H val){
		if(cont != N*M){
		A->reset();
		Lista<H>* aux = A->next();
		while(A->hasNext() && aux->size() == M){
			aux = A->next();
		}
			aux->add(val);
			cont++;
		}
		else if(cont == N*M){
			B->reset();
			Lista<H>* aux = B->next();
			while(B->hasNext() && aux->size() == P){
				aux = B->next();
			}
				aux->add(val);
				
		}
		/*if(A->size != N){
			Lista<H>* aux = A->getKey();
			if(aux->size() != M)
				aux->add(val)
		}*/
	}

	void moltiplicazione(){
		int T;
		A->reset(),B->reset(),C->reset();
		Lista<H>* a,*b,*c;
		a = A->next();
		b = B->next();
		c = C->next();
		for(int i=0; i<N; i++){
			for(int j=0; j<P; j++){
				H val = 0;
				//C[i][j] = 0;
				for(int k=0; k<M; k++) T = a->search(k) * b->search(j), val += T, b = B->next();
				c->add(val);
			B->reset();
			b = B->next();
			}
		a = A->next();
		c = C->next();	
		}
	}

	void print(ofstream& output){
		
		moltiplicazione();
		C->reset();
		while(C->hasNext()){
			C->next()->print(output);
		}
		output << endl;
	}
	
};

void metodo(ifstream& input, ofstream& output){
	int N,M,P, val;
	input >> N >> M >> P;
	lmatrix<int>* l = new lmatrix<int>(N,M,P);

	for(int i=0; i<(N*M)+(M*P); i++){
		input >> val;
		l->add(val);
	}
	l->print(output);
}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");

	for(int i=0; i<100; i++){
		metodo(input, output);
	}
	return 0;
}
