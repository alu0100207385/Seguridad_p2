#include "rc4.hpp"

using namespace std;

RC4::RC4 (vector<int> sem, vector<int> men)
{
    for (int i=0; i<MAX; i++)
      S.push_back(i);
    for (int i=0; i<MAX; i++)
      K.push_back(sem[i % sem.size()]);
    M = men;
}


string RC4::get_S(void)
{
    stringstream aux;
    unsigned salto = 0;
    for (int i=0; i<MAX; i++)
    {
      if (salto==25){
	salto=0; aux << "\n";
      }
	aux << S[i];
	aux << " ";
	salto++;
    }
    aux << "]";
    return aux.str();
}

string RC4::get_K(void)
{
    stringstream aux;
    for (int i=0; i<MAX; i++)
    {
	aux << K[i];
	aux << " ";
    }
    aux << "]";
    return aux.str();
}

string RC4::get_M(void)
{
    stringstream aux;
    for (int i=0; i<M.size(); i++)
    {
	aux << M[i];
	aux << " ";
    }
    aux << "]";
    return aux.str();
}

void RC4::intercambio (int i, int j)
{
//intercambiamos S[i] y S[j]
    int swap = S[i];
    S[i] = S[j];
    S[j] = swap;
}

//Key Scheduling Algorithm(KSA)
void RC4::KSA (void)
{
    int j = 0;
    for (int i=0; i<MAX; i++)
    {
//         cout<<"Iteracion "<<i<<endl;
	j = (j + S[i] + K[i]) % MAX;
	//intercambiamos S[i] y S[j]
// 	cout<<"Intercambio "<<i<<" con "<<j<<endl;
// 	getchar();
	intercambio (i,j);
    }
}

void RC4::KSA_paso_a_paso (void)
{
    int j = 0;
    for (int i=0; i<MAX; i++)
    {
	cout<<"S["<<i<<"]= "<<S[i]<<", K["<<i<<"]= "<<K[i];
	int aux = S[i];
	j = (j + S[i] + K[i]) % MAX;
	//intercambiamos S[i] y S[j]
	intercambio (i,j);
	cout<<" produce f= "<<j<<", S["<<i<<"]= "<<S[i]<<", S["<<j<<"]= "<<S[j]<<endl;
    }
}


//Generacion de secuencia cifrante(PRGA)
int RC4::PRGA (int &i, int &j)
{
    i = (i+1);
    if (i >= MAX)
       i %= MAX;
    j = (j+S[i]);
    if (j >= MAX)
       j %= MAX;
    //intercambiamos S[i] y S[j]
    intercambio (i,j);
    int t = (S[i] + S[j]);
    if (t >= MAX)
      t %= MAX;
    //Usar valor de S[t]
    return t;
}


void RC4::PRGA_paso_a_paso (void)
{
    vector<int> C = M;
    int k=0; int l=0;
    for (int i=0; i<M.size();i++)
    {
      	vector<int> bin;
	int aux = PRGA(k,l);
	to_binary(S[aux],bin);
	cout<<"\nByte "<<i+1<<" de secue cifrante: Salida= S["<<aux<<"]= "<<S[aux]<<":\t"<<mostrar_byte(bin)<<endl;
	
	bin.clear(); to_binary(M[i],bin);
	cout<<"Byte "<<i+1<<" de texto original: Entrada: M["<<i+1<<"]= "<<M[i]<<":\t"<<mostrar_byte(bin)<<endl;
	
	vector<int> bin_s;
	to_binary(S[aux],bin_s);

	//Rellenamos de 0 si fuera necesario
	bin_s.insert(bin_s.begin(),(8-bin_s.size()),0);
	bin.insert(bin.begin(),(8-bin.size()),0);
     
 	C[i] = to_int(XOR (bin_s,bin));
 	bin.clear(); to_binary(C[i],bin);
	cout<<"Byte "<<i+1<<" de texto cifrado: Salida= C["<<i+1<<"]= "<<C[i]<<":\t"<<mostrar_byte(bin)<<endl;
    }
}

//Pasa un int a binario
void RC4::to_binary(int n, vector<int> &bin)
{
    int d = n;
    if (n > 1)
    {
        d = n % 2;
        to_binary(n / 2, bin);
    }
    bin.push_back(d);
}

//Pasa un binario a int
int RC4::to_int(vector<int> aux)
{
    int b[]={128,64,32,16,8,4,2,1};
    int r=0;
    for (int i=aux.size()-1; i>-1;i--)
    {
	if (aux[i]==1)
	  r += b[i];
    }
    return r;
}

string RC4::mostrar_byte(vector<int> bin)
{
    stringstream aux;
    if (bin.size() < 8) //Rellenamos los bits a 0 si fuera necesario
      for (int i=0; i< (8-bin.size()); i++)
	  aux << "0 ";
  
    for (int i=0; i<bin.size(); i++)
    {
	aux << bin[i];
	aux << " ";
    }
    return aux.str();
}


vector<int> RC4::XOR (vector<int> s, vector<int> m)
{	  
    vector<int> r;
    for (int i=0; i<8; i++)
    {
	if ((s[i]+m[i]) > 1)
	    r.push_back(0);
	else
	  r.push_back(s[i]+m[i]);
    }
    return r;
}
