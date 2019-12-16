#include<iostream>
#include<fstream>
using namespace std;


void CaricaVett(int* a, int n, ifstream& input){
	for(int i = 0; i < n; i++){
		input>>a[i];
	}
}

void StampaVett(int* a, int n, ofstream& output){
	for(int i = 0; i < n; i++){
		output<<a[i]<<" ";
	}
	
}

void merge(int v[], int low, int mid, int high) {
	int b[50];
	int h = low;
	int i = low;
	int j = mid+1;

	while( (h<=mid) && (j<=high) ) {
		if(v[h] <= v[j]) b[i] = v[h++];
		else b[i] = v[j++];
  		i++;
	}
 	if(h>mid)
  		for(int k=j; k<=high; k++) b[i++]=v[k];
 	else
		for(int k=h; k<=mid; k++) b[i++]=v[k];
 	for(int k=low; k<=high; k++) v[k]=b[k];
 	
 	
}

void mergesort(int *v, int low, int high, int& cont) {

	if( low<high ) {
		cont+=v[low];
		int mid = (low+high)/2;
		mergesort( v, low, mid, cont);
		mergesort( v, mid+1, high, cont );
		merge( v, low, mid, high);
 	}
}

void metodo(ifstream& input, ofstream& output){
	int N;
	input>>N;
	int cont = 0;
	int *vett = new int[N];
	CaricaVett(vett, N, input);
	mergesort(vett, 0, N-1, cont);
	
	output <<cont << endl;
}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");

	for(int i = 0; i < 100; i++)
		metodo(input, output);
	return 0;
}
