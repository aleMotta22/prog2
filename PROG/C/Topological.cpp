#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
fstream f1, f2;
template <class H> class Node{
	private:
		H key;
		Node<H> *next;
	public:
		Node(H x){
			key=x;
			next=NULL;
		}
		void setKey(H x){
			key=x;
		}
		void setNext(Node<H> *tmp){
			next=tmp;
		}
		H getKey(){
			return key;
		}
		Node<H>* getNext(){
			return next;
		}
};
template <class H> class Queue{
	private:
		Node<H> *head;
	public:
		Queue(){
			head=NULL;
		}
		void enQueue(H x){
			Node<H> *app=new Node<H>(x);
			app->setNext(head);
			head=app;
		}
		Node<H>* deQueue(){
			Node<H> *tmp=head;
			head=head->getNext();
			return tmp;
		}
		void print(){
			Node<H> *tmp=head;
			while(tmp!=NULL){
				f2 << tmp->getKey() << " ";
				tmp=tmp->getNext();
			}
			f2 << endl;
		}
};
template<class H>
class Grafo{
private:
    H *vettore;
    bool **matrice;
    int n, nKeys;
    string *colore;
    H *valori;
    Queue<H> *list;
public:
    Grafo(int n)
    {
        this->n=n;
        nKeys=0;
        matrice=new bool *[n];
        list=new Queue<H>();
        vettore=new H[n];
        colore=new string[n];
        valori=new H[n];
        for(int i=0; i<n; i++)
        {
            matrice[i]=new bool[n];
            for(int j=0;j<n;j++)
            {
                matrice[i][j]=0;
            }
        }
    }
    void DFS()
    {
        for(int i=0; i<n;i++)
        {
            colore[i]="W";
        }
        for(int j=0;j<n;j++)
        {
            if(colore[j]=="W")
            {
                DFSvisit(j);
            }
        }
    }
    void DFSvisit(int i)
    {
        colore[i]="G";
        for(int j=0;j<n;j++)
        {
            if(matrice[i][j]==1)
            {
                if(colore[j]=="W")
                {
                    DFSvisit(j);
                }
            }
        }
        colore[i]="B";
        list->enQueue(vettore[i]);
    }
    void TopologicalSort(){
			DFS();
			list->print();
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
    /*void print(){
            for (int i=0; i<n; i++){
                f2<<"("<<vettore[i]<<" "<<start[i]<<" "<<end[i]<<") ";
            }
            f2<<endl;
        }*/
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
            grafo->TopologicalSort();
            //grafo->print();
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
            grafo->TopologicalSort();
            //grafo->print();
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
            grafo->TopologicalSort();
            //grafo->print();
        }
    }
}
