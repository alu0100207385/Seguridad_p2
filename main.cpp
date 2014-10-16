//ALUMNO: Aaron Socas Gaspar
//Seguridad curso 2013-2014
//Practica 2: RC4

#include "rc4.hpp"
#include "pause.hpp"

vector<int> entrada (int ini, int fin, char* argv[])
{
      vector<int> aux;
      for (int i=ini; i<fin; i++)
      {
	if (atoi(argv[i]) < 0) //controlamos los negativos
	  aux.push_back(atoi(argv[i]) * -1);
	else
	  aux.push_back(atoi(argv[i]));
      }
      return aux;
}

string mostrar(vector<int> v, int fin)
{
    stringstream aux;
    for (int i=0; i<fin; i++)
    {
      aux << v[i];
      aux << " ";
    }
    return aux.str();
}

using namespace std;

int main (int argc, char* argv[])
{
  if ((argc==1)||(argc != (atoi(argv[1])+atoi(argv[2]) + 3)))
  {
      cout<<"Error de argumentos"<<endl;
      cout<<"Introduzca n_semillas n_text [semillas] [texto]"<<endl;
      cout<<"Ej. ./rc4 2 2 4 50 3 12"<<endl;
      return -1;
  }
  else
  {
      vector<int> semilla = entrada(3, atoi(argv[1]) + 3, argv);
/*      int fin = atoi(argv[1]) + 3;
      for (int i=3; i<fin; i++)
      {
	if (atoi(argv[i]) < 0) //controlamos los negativos
	  semilla.push_back(atoi(argv[i]) * -1);
	else
	  semilla.push_back(atoi(argv[i]));
      }
      */
      cout<<"Semilla de clave: "<<mostrar(semilla,semilla.size())<<endl;
      
      vector<int> mensaje = entrada(3 + atoi(argv[1]), 3 + atoi(argv[2]) + atoi(argv[1]), argv);
/*      int inicio = 3 + atoi(argv[1]);
      int fin = 3 + atoi(argv[2]) + atoi(argv[1]);
      for (int i= inicio; i<fin; i++)
      {
	if (atoi(argv[i]) < 0) //controlamos los negativos
	  mensaje.push_back(atoi(argv[i]) * -1);
	else
	  mensaje.push_back(atoi(argv[i]));
      }*/
      cout<<"Text original: "<<mostrar(mensaje,mensaje.size())<<endl;

      RC4 g(semilla, mensaje);
//       cout<<"S= ["<<g.get_S()<<endl;
//       cout<<"K= ["<<g.get_K()<<endl;
      
      g.KSA();
//       g.KSA_paso_a_paso();
      cout<<"\nS= ["<<g.get_S()<<endl;
      pause();
      g.PRGA_paso_a_paso();

  }
  return 0;
}
