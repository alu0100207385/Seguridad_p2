#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;
const int MAX = 256;

class RC4
{
private:
  vector<int> S;	//Caja S
  vector<int> K;	//Clave
  vector<int> M;	//Mensaje
  void intercambio (int i, int j);
  void to_binary(int n, vector<int> &bin);
  int to_int(vector<int> aux);
  string mostrar_byte (vector<int> bin);
  vector<int> XOR (vector<int> s, vector<int> m);
public:
  RC4 (vector<int> sem, vector<int> men);
  inline ~RC4(void){};
  string get_S(void);
  string get_K(void);
  string get_M(void);
  void KSA (void);
  void KSA_paso_a_paso (void);
  int PRGA (int &i, int &j);
  void PRGA_paso_a_paso (void);
};
