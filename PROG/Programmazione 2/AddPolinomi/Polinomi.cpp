#include <iostream>
#include<fstream>

using namespace std;


class Monomio{
	private:
		int coeff;
		int esp;
		Monomio* succ;
		Monomio* prec;
	public:
		Monomio(){coeff=esp=0; succ=prec=NULL;}
	    Monomio(int c, int e){coeff=c; esp=e;}
		int getCoeff() const{ return coeff; }
		int getEsp() const { return esp;}
		void setCoeff(int c){ coeff=c; }
		void setEsp(int e){ esp=e; }
		void setSucc(Monomio* s){succ=s;}
		void setPrec(Monomio* s){succ=s;}
		Monomio* getSucc(){return succ;}
		Monomio* getPrec(){return prec;}
		
};
int operator<(const Monomio& a, const Monomio& b) {
    return  (a.getEsp() < b.getEsp());
}
//int operator==(const Monomio& a, const Monomio& b) {
  //  return  (a.getEsp() == b.getEsp());
//}

int operator>(const Monomio& a, const Monomio& b) {
    return  (a.getEsp() > b.getEsp());
}


class Polinomio{
	private:
		Monomio* testa;
	public:
		Polinomio() { testa = NULL; }
		
		/*void insertP(int c, int e) {
			Monomio* m = new Monomio(c, e);
			if (coda == NULL) {
			    coda = testa = m;
		    }
			else {
				Monomio* tmp = coda;
			    coda = search(m);
			    coda->setSucc(tmp);
			}
		}*/
		void insertP(int c, int e) {
			Monomio* newm = new Monomio(c,e);
			if (testa) {
				newm->setSucc(testa);
				newm->setPrec(NULL);
				testa->setPrec(newm);
				testa = newm;
			}
			else {
				testa = newm;
				newm->setPrec(NULL);
				newm->setSucc(NULL);
			}
		}
		/*Monomio* search(Monomio* m){
			Monomio* tmp=coda;
			while(tmp){
				if(m->getEsp()==tmp->getEsp()){
					m->setCoeff(tmp->getCoeff()+m->getCoeff());
					return m;
				   }
				else{
					tmp=tmp->getSucc();
				}   
			}
			return m;
		}*/
		void stampaP(){
			Monomio* tmp = testa;
			if (!tmp)
				cout << "Polinomio vuoto!";
			while (tmp) {
				cout << tmp->getCoeff() << "x^" << tmp->getEsp() << " ";
				tmp = tmp->getSucc();
				cout << tmp->getCoeff() << "x^" << tmp->getEsp() << " ";
			}
		}
};

int main(){
	Polinomio* p = new Polinomio();
	p->insertP(2,3);
	p->insertP(3,4);
	p->insertP(1,4);
	p->stampaP();
}
