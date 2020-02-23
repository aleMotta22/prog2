#include<iostream>
#include<fstream>
using namespace std;

class lista
{
public:
	lista(int cont){
		contatore = cont;
		Maggiore = 0;
		K = new int[contatore];
		N = new int[contatore];

		for(int i = 0; i < contatore; i++){
			K[i] = N[i] = -2;
		}
	}

	void Inserimento(int val){
		//cout << "Inserisco : " << val << endl;
		if(K[0] == -2){
			/*cout << "Prima:" << endl;
			this->Stampa();*/
			K[0] = val;
			N[0] = -1;
			Maggiore = val;
			indice_m = 0;
			/*cout << "Dopo:" << endl;
			this->Stampa();*/
		}
		else{

			int i = 0;
			while(K[i] != -2){
				i++;
			}

			if(val>=Maggiore){
				Maggiore = val;
				indice_m = i;
			}
			/*cout << "Prima:" << endl;
			this->Stampa();*/
			K[i] = val;

			for(int j = 0; j <=  i; j++){
				N[j] = TrovaSucc(K[j], j, indice_m);
			}
			/*cout << "Dopo:" << endl;
			this->Stampa();*/
		}
		//cout << endl;
	}


	void Stampa(ofstream& output){
		//cout << "N[]: ";
		//for(int i = 0; i < contatore; i++)
			//cout << N[i] << " ";
		//cout << "\tK[]: ";
		for(int i = 0; i < contatore; i++)
			//cout << K[i] << " ";
			output << N[i] << " ";
		//cout << endl;
		output << endl;
	}

private:
	int Maggiore;
	int indice_m;
	int contatore;
	int* K;
	int* N;

	int TrovaSucc(int val, int index, int m){
		if(index == m){
			//cout << "Val " << val << " e' maggiore di " << Maggiore << endl;
			return -1;
		}
		else{
			int ris;
			int aux = 10001;
			for(int i = 0; i < contatore; i++){
				
				
				if(K[i]>=val && aux>K[i] && i!=index){
					if(K[i]>val){
						aux = K[i];
						ris = i;
					}	
					else if(K[i] == val && i > index)
						return i;

				}
			}
			return ris;
		}
	}
};


void metodo(ifstream& input, ofstream& output) {
	int N;
	input>>N;

	lista* l = new lista(N);
	int val;
	for(int i = 0; i < N; i++){
		input>>val;
		l->Inserimento(val);
	}

	l->Stampa(output);
	//cout << endl;

}

int main(){
	ifstream input("input.txt");
	ofstream output("output.txt");

	for(int i = 0; i < 100; i++)
		metodo(input, output);
	return 0;
}