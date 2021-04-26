#!/bin/bash
#liste les vendredis 13 de l'annee passee en argument

#for annee in $*
#do
#    for mois in {1..12}
#    do
#        date -d $mois/13/annee
#    done | grep vendredi
#done

for annee in $*
do
    for mois in {1..12}
    do
       if cal $mois $annee | grep -q '8.*13'
           then echo $mois $annee
       fi
    done
done

