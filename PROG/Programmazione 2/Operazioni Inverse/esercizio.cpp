#include <iostream>
#include <fstream>

using namespace std;

void opInv(ofstream& out, int r1, int r2){
	int res1,res2;
	int tmp=r1+r2;
	if(tmp%2==0){
	   res1=tmp/2;
	   if(r1>r2)
	      res2=r1-tmp;
	   else
	      res2=r2-tmp;   
    }
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	for(int i=0; i<3; i++){
		
	}
	
}
