#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int selectionSort(float A[], int n){
	int i,j,indmin;
	int cont=0;
	float aux;
	for(i=0; i<n-1; i++){
		indmin=i;
		for(j=i+1; j<n; j++)
			if(A[j]<A[indmin])
			   indmin=j;
				
	aux=A[indmin];
	A[indmin]=A[j];
	A[i]=aux;
	cont=cont+(abs(indmin-i));	
	}
	return cont;
}

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i=0; i<3; i++){
		int n; in>>n;
		float vett[n];
		for(int j=0; j<n; j++)
		   in >> vett[j];
		   
		out << selectionSort(vett,n) << endl;   
	}
}
