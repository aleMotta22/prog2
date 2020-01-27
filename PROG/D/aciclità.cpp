#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
fstream f1, f2;
template<class H>
class Grafo{
private:
    H *vettore;
    bool **matrice;
    int n, nKeys;
    string *colore;
    int *start, * end;
public:
    Grafo(int n)
    {
        this->n=n;
        nKeys=0;
        matrice=new bool *[n];
        vettore=new H[n];
        colore=new string[n];
        start=new int[n];
        end=new int[n];
        for(int i=0; i<n; i++)
        {
            matrice[i]=new bool[n];
            for(int j=0;j<n;j++)
            {
                matrice[i][j]=0;
            }
        }
    }
    int DFS()
    {
        int cycle=0;
        for(int i=0; i<n;i++)
        {
            colore[i]="W";
        }
        for(int j=0;j<n;j++)
        {
            if(colore[j]=="W")
            {
                DFSvisit(j,cycle);
            }
        }
        return cycle;
    }
    void DFSvisit(int i, int &cycle)
    {
        colore[i]="G";
        for(int j=0;j<n;j++)
        {
            if(matrice[i][j]==1)
            {
                if(colore[j]=="G")
                {
                    cycle++;
                }
                if(colore[j]=="W")
                {
                    DFSvisit(j,cycle);
                }
            }
        }
        colore[i]="B";
    }
    void insert(H valore)
    {
        if(nKeys<n)
        {
            vettore[nKeys]=valore;
            nKeys++;
        }
    }
    int findIndex(H valore)
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
    void addVertice(H num1, H num2)
    {
        int index1=findIndex(num1);
        int index2=findIndex(num2);
        if(index1==-1 || index2==-1)
        {
            return;
        }else
        {
            matrice[index1][index2]=1;
        }
    }
    void print(){
            for (int i=0; i<n; i++){
                f2<<"("<<vettore[i]<<" "<<start[i]<<" "<<end[i]<<") ";
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
            f2<<grafo->DFS()<<endl;
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
            f2<<grafo->DFS()<<endl;
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
            f2<<grafo->DFS()<<endl;
        }
    }
}
