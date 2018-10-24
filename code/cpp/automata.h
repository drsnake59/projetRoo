#ifndef automata_h
#define automata_h

#include <iostream>
#include <sstream>    // ostrstream, istrstream
#include <fstream>

typedef unsigned * Regle;

using namespace std;

class Automata {
public:
  /*********************************************
   * constructor
   *
   * input : N : maximum size of the automata
   *
   *********************************************/  
  Automata(int _maxSize) : nbStates(5), maxSize(_maxSize), maxIteration(2 * _maxSize - 2)
  {
    BORD  = nbStates;
    FIRE  = nbStates - 1;
    GEN   = 1;
    REPOS = 0;
  
    int i;
  
    configs = new int*[maxIteration + 1];
    for(i = 0; i <= maxIteration; i++)
      configs[i] = new int[maxSize + 2];
  }
  
  void initialConfiguration(int N) ;
  int evol(Regle regles, int N);
  int f(Regle regles, int n);
  float f2(Regle regles, int n);
  void print(int N, int nbIter, const char * fileName);
  
  private:
  // diagramme espace-temps;
  int ** configs;
  
   // nombre d'états
  int nbStates;
  
  // taille de l'automate
  int maxSize;
  
  // nombre maximum d'iterations
  int maxIteration;
 
  // notation pour certains états
  int BORD;
  int FIRE;
  int GEN;
  int REPOS;
  
  };
#endif
