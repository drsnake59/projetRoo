/**
 * 
 */
import java.io.*;

/**
 * @author verel
 *
 */
public class Automata {

	// diagramme espace-temps;
	int configs [][] ;

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


	/*********************************************
	 * constructor
	 *
	 * input : N : maximum size of the automata
	 *
	 *********************************************/  
	public Automata(int _maxSize) {
		nbStates = 5;	
		maxSize = _maxSize; 
		maxIteration = 2 * _maxSize - 2;
		BORD  = nbStates;	
		FIRE  = nbStates - 1;
		GEN   = 1;
		REPOS = 0;

		if ((maxIteration > 1) && (maxSize > 1))
			configs = new int [maxIteration + 1][maxSize + 2];
	}

	/*********************************************
	 * configuration initiale de l'automate
	 *
	 * input : N : size of the automata
	 *
	 *********************************************/
	public void initialConfiguration(int N) {
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
	public int evol(int [] regles, int N) {
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

		// nombre de fusiliers après 2N-2 it屍ations
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
	 *
	 * output : the maximum size solved
	 *
	 *********************************************/
	public int f(int [] regles, int n) {
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
     * Export the space-time diagramme of the automa
     *   into SVG format
     *
     * input : N - size of the automata
     *         nbIter - number of iterations
     *         
     *
     * output : fileName
     *
     *********************************************/
    public void exportSVG(int N, int nbIter, String fileName) {
	if (nbIter > maxIteration)
	    nbIter = maxIteration;
  
	int width  = 10;
	int height = 10;
  
	PrintWriter file;
	try {
	    file =  new PrintWriter(new BufferedWriter(new FileWriter(fileName)));
 
	    // head of the file
	    file.println("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	    file.println("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">");
	    file.println("<svg");
	    file.println("xmlns=\"http://www.w3.org/2000/svg\"");
	    file.println("xmlns:xlink=\"http://www.w3.org/1999/xlink\"");
	    file.println("xmlns:ev=\"http://www.w3.org/2001/xml-events\"");
	    file.println("version=\"1.1\"");
	    file.println("baseProfile=\"full\">");
	    file.println("<g stroke-width=\"1px\" stroke=\"black\" fill=\"white\">");
	    
	    boolean fire = false;
	    int i, j; 
	    for(i = 0; i <= nbIter && !fire; i++) {
		for(j = 1; j <= N; j++) {
		    file.print("<rect width=\"" + width + "\" " 
			       + "height=\"" + height + "\" "
			       + "x=\"" + ((j-1) * width) + "\" "
			       + "y=\"" + (i     * height) + "\" "
			       + "fill=\"");
		    
		    if (configs[i][j] == REPOS)
			file.print("white") ; 
		    else if (configs[i][j] == FIRE)
			file.print("red")  ; 
		    else if (configs[i][j] == GEN)
			file.print("blue") ; 
		    else if (configs[i][j] == 2)
			file.print("yellow") ; 
		    else if (configs[i][j] == 3)
			file.print("green") ; 
		    else
			file.print("grey") ; 
  
		    file.println("\"/>") ;
  
		    fire = fire || (configs[i][j] == FIRE);
		}
	    }
	    
	    file.println("</g> </svg>");

	    file.close();
	}
	catch (Exception e){
	    System.out.println(e.toString());
	}
    }

}
