#include <iostream>
#include <string.h>

#include "musique.h"

using namespace std;

//Constructeur
Musique::Musique() {
	titre = "non defini";
	auteur = "non defini";
	duree = 0;
}
Musique::Musique(string tit, string aut, float dur) {
	titre = tit;
	auteur = aut;
	duree = dur;
}
Musique::Musique(const Musique & m) {
	titre = m.titre;
	auteur = m.auteur;
	duree = m.duree;
}

//accesseurs
string Musique::get_titre()const {
	return titre;
}
string Musique::get_auteur()const {
	return auteur;
}
float Musique::get_duree()const {
	return duree;
}

// polymorphisme
// calcule et retourne la taille du fichier
float Musique::taille_mem ()const {
	float sec = duree*60;
	int taille_ko = sec*192;
	return taille_ko/(float)1000;
}
//methode
void Musique::affiche() {
	cout << "titre: " << titre << endl;
	cout << "auteur: " << auteur << endl;
	cout << "duree: " << duree << endl;
	cout << "taille:" << taille_mem()<< "Mo"<< endl;
}

