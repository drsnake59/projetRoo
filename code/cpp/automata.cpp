#include "automata.h"


 /*********************************************
   * configuration initiale de l'automate
   *
   * input : N : size of the automata
   *
   *********************************************/
  void Automata :: initialConfiguration(int N) {
    // bord gauche
    for(int t = 0; t <= maxIteration; t++) 
      configs[t][0]   = BORD;
  
    // bord droit
    for(int t = 0; t <= maxIteration; t++) 
      configs[t][N+1] = BORD;
  
    // repos
    for(int i = 2; i <= N; i++)
      configs[0][i] = REPOS;
  
    // général
    configs[0][1] = GEN;
  }
  
  /*********************************************
   * evolution of the automate from initial configuration
   * to the first time of firing
   *
   * input : regles : rules of the automata
   *         N : size of the automata
   *         nbIter : maximum number of iterations
   *
   * output : number of the firing after 2N-2 iteration
   *          0 else
   *********************************************/
  int Automata :: evol(Regle regles, int N) {
    int nbIter = 2 * N - 2;

    if (nbIter > maxIteration)
      nbIter = maxIteration;
  
    // initialise l'automate
    initialConfiguration(N);
  
    // nombre d'états feu
    int nbFire = 0;
    
    // valeur de la regle locale
    int r;
  
    int i, t;
  
    t = 1;
    while (t <= nbIter && nbFire == 0) {
      for(i = 1; i <= N; i++) {
        r = regles[ configs[t-1][i-1] * 36 + configs[t-1][i] * 6 + configs[t-1][i+1] ];
        	
        if (r == FIRE)
          nbFire++;
                 
        configs[t][i] = r;
      }
      
      t++;
    }
    
    // nombre de fusiliers après 2N-2 itérations
    if (t == 2 * N - 2 + 1)
      return nbFire;
    else
      return 0;
  }
  
  /*********************************************
   * compute objective function
   *
   * input : regles : rules of the automata
   *         n : maximum of automata size
   *         nbIter : maximum number of iterations
   *
   * output : the maximum size solved
   *
   *********************************************/
  int Automata :: f(Regle regles, int n) {
    int nbFireTot = evol(regles, 2);
   
    int k = 2;

    while (nbFireTot == k && k <= n) {
      k++;
      nbFireTot = evol(regles, k);
    }
  
    if (k == 2)
      return 0;
    else
      return k - 1;
  }

  /*********************************************
   * compute objective function
   *
   * input : regles : rules of the automata
   *         n : maximum of automata size
   *         nbIter : maximum number of iterations
   *
   * output : total number of firing + the fraction of synchronised fires
   *
   *********************************************/
  float Automata :: f2(Regle regles, int n) {
    int nbFireTot = evol(regles, 2);
   
    int k = 2;

    while (nbFireTot == k && k <= n) {
      k++;
      nbFireTot = evol(regles, k);
    }
  
    if (k == 2)
      return 0;
    else
      return k - 1 + ((float) nbFireTot) / k;
  }

void Automata :: print(int N, int nbIter, const char * fileName) {
    if (nbIter > maxIteration)
      nbIter = maxIteration;
  
    int width  = 10;
    int height = 10;
  
    fstream file(fileName, ios::out);
  
    if (file) {
      // head of the file
      file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" 
           << endl
           << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">" 
           << endl << endl
           << "<svg" << endl
           << "xmlns=\"http://www.w3.org/2000/svg\"" << endl
           << "xmlns:xlink=\"http://www.w3.org/1999/xlink\"" << endl
           << "xmlns:ev=\"http://www.w3.org/2001/xml-events\"" << endl
           << "version=\"1.1\"" << endl
           << "baseProfile=\"full\">" << endl
           << "<g stroke-width=\"1px\" stroke=\"black\" fill=\"white\">" << endl;
  
      bool fire = false;
      int i, j; 
      for(i = 0; i <= nbIter && !fire; i++) {
        for(j = 1; j <= N; j++) {
          file << "<rect "
               << "width=\""  << width   << "\" "
               << "height=\"" << height  << "\" "
               << "x=\"" << ((j-1) * width)  << "\" "
               << "y=\"" << (i     * height) << "\" "
               << "fill=\"";
  
          if (configs[i][j] == REPOS)
            file << "white" ; 
          else if (configs[i][j] == FIRE)
            file << "red"  ; 
          else if (configs[i][j] == GEN)
            file << "blue" ; 
          else if (configs[i][j] == 2)
            file << "yellow" ; 
          else if (configs[i][j] == 3)
            file << "green" ; 
          else
            file << "grey" ; 
  
          file << "\"/>" << endl;
  
          fire = fire || (configs[i][j] == FIRE);
        }
      }
      
      file << "</g> </svg>" << endl;
  
      file.close();
    } else
      cerr << "print: impossible to open file " << fileName << endl;    
  }
  

  
