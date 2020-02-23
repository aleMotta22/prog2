#include <iostream>
#include <fstream>
using namespace std;

int conta(int* &vett, int &n, int &x){
    int contatore = 0;
    for(int i = 0; i < n; i++)
        if(vett[i] > x)
            contatore++;
    return contatore;
}

void soluzione(int*&vett, int n, int x, ofstream& out){

    int contatore = conta(vett, n, x);
    out << contatore << " ";
    for(int i = 0; i < n; i++)
        if(vett[i] > x)
            out << vett[i] << " ";
    
    out << endl;
}

int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        int n; in >> n;
        int x; in >> x;

        int*vett = new int[n];
        for(int j = 0; j < n; j++)
            in >> vett[j];
        
        soluzione(vett, n, x, out);

        delete [] vett;
    }


    return 0;
}


