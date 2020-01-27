#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
fstream f1,f2;
template<class H>
class Grafo{
private:
    bool** matrice;
    H* vettore;
    int nKey;
    int n;
public:
    Grafo(int n)
    {
        this->n=n;//numero di valori dati dall'esercizio
        matrice=new bool*[n];//matrice in cui metterò 1 per sapere se due numeri sono collegati 0 se non lo sono
        vettore=new H[n];//vettore in cui salverò tutti i miei numeri
        nKey=0;//numero iniziale di valori presenti nel vettore
        for(int i=0; i<n;i++)
        {
            matrice[i]= new bool[n];
            for(int j=0; j<n;j++)
            {
                matrice[i][j]=0;//setto tutta la matrice di collegamenti a 0
            }
        }
    }
    void insert(H valore)
    {
        if(nKey<n)
        {
            vettore[nKey]=valore;
            nKey++;
        }
    }
    int findIndex(H valore)//lo uso per trovare la posizione di un valore presente nel mio vettore
    {
        for(int i=0; i<n; i++)
        {
            if(vettore[i]==valore)
            {
                return i;
            }
        }
        return -1;
    }
    void addVertice(H valore1, H valore2)
    {
          int index1=findIndex(valore1);
          //cout<<"primo"<<index1<<endl;
          int index2=findIndex(valore2);
          //cout<<"secondo"<<index2<<endl;
          if(index1==-1 || index2==-1)
          {
              return;
          }else
          {
              matrice[index1][index2]=1;
          }
    }
    void selectionSort()
    {
        for(int i=0; i<n; i++){
                int min = i;
                for(int j=i+1; j<n; j++){
                    if(vettore[j] < vettore[min])
                        min = j;
                }

                H temp = vettore[i];
                vettore[i] = vettore[min];
                vettore[min] = temp;
            }
    }
    void print(){
            for (int i=0; i<n; i++){
                f2<<"("<<vettore[i];
                for (int j=0;j<n;j++){
                    if (matrice[i][j]) f2<<" "<<vettore[j];
                }
                f2<<") ";
            }
            f2<<endl;
        }
        void vedoMatrice()
        {
            for(int i=0; i<n;i++)
            {
                for(int j=0; j<n;j++)
                {
                    cout<<matrice[i][j]<<"|";
                }
                cout<<endl;
            }
        }
        void vedoVett()
        {
            for(int i=0; i<n;i++)
            {
                cout<<vettore[i]<<" ";
            }
        }
};
int main()
{
    f1.open("input.txt", ios::in);
    f2.open("output.txt", ios::out);
    while(!f1.eof())
    {
        int nChiavi, nCoppie;
        string tipo, valore1,valore2;
        f1>>nChiavi>>nCoppie>>tipo;
        if(tipo=="int")
        {
            int valore, scambio1, scambio2;
            Grafo<int>* grafo = new Grafo<int>(nChiavi);
            for(int i=0;i<nChiavi;i++)
            {
                f1>>valore;
                grafo->insert(valore);
            }
            grafo->selectionSort();
            for(int i=0;i<nCoppie;i++)
            {
                stringstream cambio;
                f1>>valore1;
                valore1.erase(0,1);
                cambio<<valore1;
                cambio>>scambio1;
                cambio.clear();
                f1>>valore2;
                valore2.erase(2,2);
                cambio<<valore2;
                cambio>>scambio2;
                grafo->addVertice(scambio1, scambio2);
            }
            grafo->print();
        }
        if(tipo=="double")
        {
            double valore, scambio1, scambio2;
            Grafo<double>* grafo = new Grafo<double>(nChiavi);
            for(int i=0;i<nChiavi;i++)
            {
                f1>>valore;
                grafo->insert(valore);
            }
            grafo->selectionSort();
            for(int i=0;i<nCoppie;i++)
            {
                stringstream cambio;
                f1>>valore1;
                valore1.erase(0,1);
                cambio<<valore1;
                cambio>>scambio1;
                cambio.clear();
                f1>>valore2;
                for(int j=0;j<valore2.length();j++)
                {
                    if(valore2[j]==')')
                    {
                        valore2.erase(j,j);
                    }
                }
                cambio<<valore2;
                cambio>>scambio2;
                grafo->addVertice(scambio1, scambio2);
            }
            grafo->print();
        }
        if(tipo=="char")
        {
            char valore, scambio1, scambio2;
            string valore1, valore2;
            Grafo<char>* grafo = new Grafo<char>(nChiavi);
            for(int i=0;i<nChiavi;i++)
            {
                f1>>valore;
                grafo->insert(valore);
            }
            grafo->selectionSort();
            for(int i=0;i<nCoppie;i++)
            {
                stringstream cambio;
                f1>>valore1;
                valore1.erase(0,1);
                cambio<<valore1;
                cambio>>scambio1;
                f1>>valore2;
                valore2.erase(1,1);
                cambio<<valore2;
                cambio>>scambio2;
                grafo->addVertice(scambio1, scambio2);
            }
            grafo->print();
        }
    }
}







