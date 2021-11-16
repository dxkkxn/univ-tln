##
# music
#
# @file
# @version 0.1
#
CFLAGS=-Wall -g
main: main.o musique.o musiqueCompressee.o albumMP3.o
	g++ main.o musique.o musiqueCompressee.o albumMP3.o -o main
main.o: main.cc
	g++ $(CFLAGS) -c main.cc
musique.o: musique.h musique.cc
	g++ $(CFLAGS) -c musique.cc
musiqueCompressee.o:  musiqueCompressee.cc musiqueCompressee.h
	g++ $(CFLAGS) -c musiqueCompressee.cc
albumMP3.o: albumMP3.cc albumMP3.h
	g++ $(CFLAGS) -c albumMP3.cc

# end
