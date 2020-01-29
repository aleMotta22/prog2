#include<iostream>
#include<fstream>
#include <stdio.h>
#include <string.h>

using namespace std;


void CaricaVett(int* a, int n, ifstream& input){
	for(int i = 0; i < n; i++){
		input>>a[i];
	}
}


void StampaVett(int* a, int n){
	for(int i = 0; i < n; i++){
		cout<<a[i]<<" ";
	}
	cout<<"\n";
	
}

void StampaVett(int* a, int n, ofstream& output){
	for(int i = 0; i < n; i++){
		output<<a[i]<<" ";
	}
	
}

void merge(int *arr, int low, int high, int mid)

{

    int i, j, k, c[5001];

    i = low;

    k = low;

    j = mid + 1;

    while (i <= mid && j <= high) {

        if (arr[i] < arr[j]) {

            c[k] = arr[i];

            k++;

            i++;

        }

        else  {

            c[k] = arr[j];

            k++;

            j++;

        }

    }

    while (i <= mid) {

        c[k] = arr[i];

        k++;

        i++;

    }

    while (j <= high) {

        c[k] = arr[j];

        k++;

        j++;

    }
    for (i = low; i < k; i++)  {
        arr[i] = c[i];

    }
}


void merge2(int *a, int start, int middle, int end){
	
    middle+=1;
	int i = 0;
	int app[501];
	
	while(start <= middle && middle <= end){
 		if( a[start] < app[middle] ) {app[i] = a[start]; start++;}
 	else{ app[i] = a[middle]; middle++;}
 		i++;
 	}
 	if(start<= middle)
  		while (i <= end) {app[i] = a[start]; start++;}
 	else
		while(i<= end) {app[i] = a[middle]; middle++;} 
		cout<<app[0]<<"\n";
 	memcpy(a,&app,sizeof(a)*end+1); 
 	
 	
}

void mergesort(int v[], int low, int high, int& cont) {

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
	StampaVett(vett,N);
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
