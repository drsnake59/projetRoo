#include "automata.h"

Regle initRul(){
	Regle rules=new unsigned[n*n*n];
	
		for(int g=0;g<n;g++){
			for(int c=0;c<n;c++){
				for(int d=0;d<n;d++){
					int indice=g*36+c*6+d;
						
				}
			}
		}
	
	}

Regle initRules(char * fileName) {
  fstream file(fileName, ios::in);

  if (file.is_open()) {
    // 5 états + l'état "bord"
    unsigned n = 5 + 1;

    Regle rules = new unsigned[n * n * n];

    unsigned value;
    for(unsigned i = 0; i < n * n * n; i++) {
      file >> value;
      rules[i] = value;
    }

    return rules;
  } else
    cerr << "Impossible d'ouvrir " << fileName << endl;
}

int main(int argc, char **argv) {
  // nombre d'états de l'automate cellulaire
  int nbStates = 5;

  // Nombre maximale de fusiliers (taille maximale du réseau)
  unsigned int sizeMax = 20;

  // déclaration de l'automate cellulaire
  Automata automate(sizeMax);

  // initialise l'automate à partir d'un fichier
  char str[256];
  sprintf(str, "%s.dat", argv[1]);

  //Regle rules = initRules(str);
 
  Regle r=initRul();
  
  // calcul de la performance de rules dans un automate de taille maximale 20
  cout << automate.f(rules, 20) << endl;
  
  unsigned nFire ;

  for(unsigned i = 2; i <= sizeMax; i++) {
    // évolution de l'automate avec la règle rule sur un réseau de longueur i
    nFire = automate.evol(rules, i);

    // affichage du nombre de fusiliers ayant tiré
    cout << "longueur " << i << " : " << nFire << endl;

    // affiche la dynamique dans un fichier au format svg
    sprintf(str, "svg/%s_%d.svg", argv[1], i);
    automate.print(i, 2 * i - 2, str);
  } 

}
