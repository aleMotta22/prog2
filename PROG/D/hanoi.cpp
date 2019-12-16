#include<iostream>
#include<fstream>

using namespace std;

int passi;


void hanoi(int,int,int,int,int,ofstream&);


int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, m;
	for(int i=0; i<100; i++){
		in>>n>>m;
		passi=0;
		hanoi(n,m,1,3,2,out);
		out<<endl;
	}
}

void hanoi(int dischi, int m,int a,int b,int c, ofstream& out){
	if(dischi==1){
		passi++;
		if(passi==m) out << a <<" "<< b;
	}
	else{
		hanoi(dischi-1,m,a,c,b,out);
		hanoi(1,m,a,b,c,out);
		hanoi(dischi-1,m,c,b,a,out);
	}
}
