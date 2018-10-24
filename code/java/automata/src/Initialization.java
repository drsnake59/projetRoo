/**
 * 
 */

import java.util.Random;

/**
 * @author verel
 *
 */
public class Initialization {

	int nbRules = 216;
	
	Random generator;
	
	public Initialization() {
		generator = new Random();
	}
	
	public void init(int [] rules) {
		for(int i = 0; i < nbRules; i++)
			rules[i] = generator.nextInt(4);
	
		// les regles repos (obligatoires)
		setRule(rules, 0, 0, 0, 0);
		setRule(rules, 5, 0, 0, 0);
		setRule(rules, 0, 0, 5, 0);
		
		// les regles feu (trés conseillés)
		setRule(rules, 1, 1, 1, 4);
		setRule(rules, 5, 1, 1, 4);
		setRule(rules, 1, 1, 5, 4);
		
		// les regles a priori (signal de période 2 vers la droite)
		setRule(rules, 1, 0, 0, 2);
		setRule(rules, 2, 0, 0, 1);

		// a priori bord droit
		setRule(rules, 1, 0, 5, 1); // pour taille 2
		setRule(rules, 2, 0, 5, 2);
		
		// a priori bord gauche (pour la taille 2)
		setRule(rules, 5, 1, 0, 1);
	}

    /*
     * Ecrit la regle 
     *
     * g : etat de la cellule de gauche
     * c : etat de la cellule centrale
     * d : etat de la cellule de droite
     * r : etat de la cellule centale à t+1
     */
    public void setRule(int [] rules, int g, int c, int d, int r) {
	rules[g * 36 + c * 6 + d] = r;
    }
}
