#include <iostream>

#include "musique.h"
#include "musiqueCompressee.h"

using namespace std;

	//constructeurs//par défaut pas de compression
MusiqueCompressee::MusiqueCompressee() {
	perte = false;
	algo = "null";
	taux = 0;
}
MusiqueCompressee::MusiqueCompressee(string tit, string aut, float dur,
									 bool per, string ag, float tx):Musique(tit, aut, dur) {
	perte = per;
	algo = ag;
	taux = tx;
}

MusiqueCompressee::MusiqueCompressee(const MusiqueCompressee & mc):Musique(mc) {
	perte = mc.perte;
	algo = mc.algo;
	taux = mc.taux;
}
//polymorphisme ;// calcule la taille du fichier
float MusiqueCompressee::taille_mem ()const {
	float taille_init = this->Musique::taille_mem();
	return (taille_init - taille_init * (taux/100)) ;
}
	//surcharge de l'opérateur <<
ostream & operator<<(ostream & out, const MusiqueCompressee & mc ) {
	out << mc.Musique::get_titre() << mc.Musique::get_auteur() << endl;
	out << mc.taille_mem()<< endl;
	return out;
}
