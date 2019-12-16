#include<iostream>
#include<fstream>

using namespace std;

int insertionSort(int* V, int n){
	int i, j;
	int count = 0;
	for (i = 1; i < n; i++) {
		j = i;
		while (j > 0 && V[j - 1] > V[j]){
			V[j] = V[j - 1];
		    j--;
			count++;
			}
		V[j] = V[i];
	}
	return count;
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	for (int i = 0; i < 3; i++) {
		int n;
		in >> n;
		int *vett=new int[n];
		for (int j = 0; j < n; j++)
			in >> vett[j];
		
		out << insertionSort(vett, n) << endl;
		

	}

}