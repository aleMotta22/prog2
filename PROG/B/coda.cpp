#include <iostream>
#include <fstream>
#include <sstream>

#define ICICLO 100
using namespace std;




template <class G> class Queue {
private:
	int len, n, tail, head, current;
	G** v;
public:
	static G HNULL;
	Queue() {
		n = 0;
		len = 200;
		v = new G * [len];
		head = tail = 0;
	}
	Queue(int len) {
		n = 0;
		this->len = len;
		v = new G * [len];
		head = tail = 0;
	}

	Queue<G>* enqueue(G x) {
		if (n == len) return this;
		v[tail] = new G(x);
		tail = (tail + 1) % len;
		n++;
		return this;
	}

	G dequeue() {
		if (n == 0) return HNULL;
		G r = *v[head];
		head = (head + 1) % len;
		n--;
		return r;
	}

	int size() { return n; }
	int isEmpty() { return (n == 0); }

	void reset() { current = 0; }
	G* next() {
		if (current == n) return NULL;
		G* r = v[(head + current) % len];
		current++;
		return r;
	}
	int has_next() {
		return (current < n);
	}
};

template<> int Queue<int>::HNULL = -1;
template<> bool Queue<bool>::HNULL = false;
template<> double Queue<double>::HNULL = -1;
template<> char Queue<char>::HNULL = ' ';


template <class H> 
ostream& operator<<(ostream& out, const Queue<H>& q1) {
	Queue<H> q = q1;
	q.reset();

	while (H * i = q.next()) {
		out << *i;
		if (q.has_next()) out << ", ";
	}
	return out;
}



int main(){
	
	fstream f1,f2;
	
	f1.open("input.txt",ios::in);
	f2.open("output.txt",ios::out);
	
	int n = 0;
	string type;
	string let = "";
	for(int i=0;i<ICICLO;i++){			
		f1>>type>>n;

		char p = type[0];
		switch(p){
			case 'i':{
				Queue<int> * codaInt = new Queue<int>;
				int fInt;
				for(int j=0;j<n;j++){
					f1>>let;
					if(let[0] == 'i'){
					    std::istringstream ss(let.substr(1));
						ss >> fInt;
						codaInt->enqueue(fInt);
						}
					else
						codaInt->dequeue();
					}
					f2<<*codaInt<<" ";
			break;}
			case 'd':{		
			Queue<double> *codaDouble = new Queue<double>;
					double fDouble;
					for(int j=0;j<n;j++){
						f1>>let;
				
						if(let[0]== 'i'){
							istringstream ss(let.substr(1));
							ss >> fDouble;
							codaDouble->enqueue(fDouble);
							}
						else
					codaDouble->dequeue();
					}
				f2<<*codaDouble<<" ";
					
			    break;
			}
				case 'c':{
				Queue<char> *codaChar = new Queue<char>;
					char fChar ;
					for(int j=0;j<n;j++){
								f1>>let;
								if(let[0] == 'i')
								codaChar->enqueue(let[1]);
								else
								codaChar->dequeue();
					}
							f2<<*codaChar<<" ";			
				break;
			}
				case 'b':
					{
					
				Queue<bool> *codaBool = new Queue<bool>;
					bool fBool;
					for(int j=0;j<n;j++){
								f1>>let;
								if(let[0] == 'i'){
								istringstream  ss(let.substr(1));
								ss >> fBool;
									codaBool->enqueue(fBool);
								}
								else
								codaBool->dequeue();
					}
					f2<<*codaBool<<" ";
						break;
			}
		
		}
		f2<<"\n";
		
		
	}
return 0;

}


















