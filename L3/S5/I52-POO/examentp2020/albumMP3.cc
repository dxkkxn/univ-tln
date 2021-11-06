#include "albumMP3.h"
	//constructeurs
AlbumMP3::AlbumMP3() {
	album = NULL;
	nbtitre = 0;
}
//construction d'une instance dont le nombre de morceaux est fourni en paramètre

AlbumMP3::AlbumMP3(int n) {
	album = new MusiqueCompressee[n];
	nbtitre = n;
}

AlbumMP3::AlbumMP3(MusiqueCompressee* arr_mc, int n) {
	nbtitre = n;
	album = new MusiqueCompressee [n];
	for(int i = 0; i < n; i++)
		album[i] = arr_mc[i];
}

AlbumMP3::AlbumMP3(const AlbumMP3 & amp3) {
	nbtitre = amp3.nbtitre;
	album = new MusiqueCompressee [amp3.nbtitre];
	for(int i = 0; i < nbtitre; i++) {
		album[i] = amp3.album[i];
	}
}
AlbumMP3::~AlbumMP3() {
	delete[] album;
}

//surcharge de l'opérateur =

const AlbumMP3 & AlbumMP3::operator=(const AlbumMP3 & amp3) {
	if (this != &amp3) {
		delete[] album;
		nbtitre = amp3.nbtitre;
		album = new MusiqueCompressee[nbtitre];
		for (int i = 0; i < nbtitre; i++) {
			album[i] = amp3.album[i];
		}
	}
	return *this;

}

//surcharge de l'opérateur + qui ajoute un morceau de musique à mon album courant
AlbumMP3 AlbumMP3::operator+(const MusiqueCompressee & mc) {
	AlbumMP3 res;
	res.album = new MusiqueCompressee[nbtitre + 1];
	res.nbtitre = nbtitre + 1;
	int i;
	for(i = 0; i < nbtitre; i++)
		res.album[i] = album[i];
	res.album[i] = mc;
	return res;
}

//surcharge de l'opérateur + qui ajoute une instance de la classe AlbumMP3 à une instance
//de la classe MusiqueCompressee
AlbumMP3 operator+(const MusiqueCompressee & mc, const AlbumMP3 & amp3) {
	AlbumMP3 res;
	res.album = new MusiqueCompressee[amp3.nbtitre + 1];
	res.nbtitre = amp3.nbtitre + 1;
	int i;
	for(i = 0; i < amp3.nbtitre; i++)
		res.album[i] = amp3.album[i];
	res.album[i] = mc;
	return res;
}

//surcharge de l'opérateur []
//retourne la taille de l'album en Mo
float AlbumMP3::taille_album() {
	float res = 0;
	for(int i = 0; i < nbtitre; i++)
		res += album[i].taille_mem();
	return res;
}
