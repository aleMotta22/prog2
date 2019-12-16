#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define ICICLO 100

using namespace std;

template <class G>
class Stack{
	private:
		int n,top,current,len;
		G ** v;
		
	public:
	static G GNULL;
	Stack(){
		n = top = current = 0;
		len = 200;
		v = new G*[len];
	}	
		
		
	Stack<G> * push(G x){
		if(n==len)return this;
		v[top] = new G(x);
		top++;
		n++;
		return this;

	}
	
	G * pop(){
		if(top == 0)return &GNULL;
		top--;
		n--;
		G * f = v[top];
		return f;
		
	}
					
	void reset() { current = top - 1; }
	G* next() {
		if (current < 0) return NULL;
		G* r = v[current];
		current--;
		return r;
	}
	bool has_next() {
		return (current < n);
	}
	int size() { return n; }
	int isEmpty() { return (n == 0); }
	
};


template<> int Stack<int>::GNULL = -1;
template<> bool Stack<bool>::GNULL = false;
template<> char Stack<char>::GNULL = ' ';
template<> double Stack<double>::GNULL = -1.0;

template <class G>
ostream& operator<<(ostream& out, const Stack<G>& l) {
	Stack<G> t = l;
	t.reset();
	while (t.has_next()) out << *(t.next()) << " ";
	return out;
}

int main(){
	
	fstream f1,f2;

	int n;
	string type;
	
	f1.open("input.txt",ios::in);
	f2.open("output.txt",ios::out);
	
	for(int i=0;i<ICICLO;i++){
		
		f1>>type>>n;
		
		char p = type[0];		
		string op ="";
		
		switch(p){
			case 'i':{
				Stack<int> * stackInt = new Stack<int>;		
				int fInt=0;
				for(int j=0;j<n;j++){
					f1>>op;
					if(op[0]=='i'){	
					std::istringstream ss(op.substr(1));
					ss >> fInt;
					stackInt->push(fInt);
				}
					else{
						stackInt->pop();
					}
				}
				f2<<*stackInt<<" ";
			break;
			}
			case 'c':{
				Stack<char> * stackChar = new Stack<char>;
				char fChar;
				for(int j=0;j<n;j++){
					f1>>op;
	
					if(op[0]=='i')
						stackChar->push(op[1]);
					else
						stackChar->pop();
				}
				 f2<<*stackChar<<" ";
			break;
			}
			case 'd':{
				Stack<double> * stackDouble = new Stack<double>;
				double fDouble;
				for(int j=0;j<n;j++){
					f1>>op;
					if(op[0]=='i'){	
					std::istringstream ss(op.substr(1));
					ss >> fDouble;
					stackDouble->push(fDouble);
				}
					else{
						stackDouble->pop();
					}
				}
					f2<<*stackDouble<<" ";
				break;
			}
			case 'b':{
				Stack<bool> * stackBool = new Stack<bool>;
				int fBool;
				for(int j=0;j<n;j++){
					f1>>op;
					if(op[0]=='i'){
						cout<<op[0];
						std::istringstream ss(op.substr(1));
						ss >> fBool;
						cout<<"fboll"<<n << " -"<<j ;
					if(fBool == 0){
						stackBool->push(false);
						}
						else{
						stackBool->push(true);	
						
					}
					}
					else
						stackBool->pop();
				}
					f2<<*stackBool<<" ";
					break;
			}
			
		}
		f2<<"\n";
		
	}
	
	
}





