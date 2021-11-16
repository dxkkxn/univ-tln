#ifndef _MUSIQUE
#define _MUSIQUE

#include <string>
using namespace std;

class Musique{
private : 
	string titre;//titre du morceau de musique
	string auteur;//nom de l'auteur/interprète
	float duree;// temps en minutes
	
public:
//Constructeur
	Musique();
	Musique(string, string, float);
	Musique(const Musique &);
//accesseurs
	string get_titre()const;
	string get_auteur()const;
	float get_duree()const;

// polymorphisme
	float taille_mem ()const;// calcule et retourne la taille du fichier 	
//methode
	void affiche();	

};
#endif
	 
