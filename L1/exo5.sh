mkdir /home/etudiants/ybenjello021/photo
mkdir /home/etudiants/ybenjello021/texte
mkdir /home/etudiants/ybenjello021/video
LISTPHOTOS=$(ls /home/perso/paiement/O12_TP/exercice_3/atrier/*.png)
LISTVIDEO=$(ls /home/perso/paiement/O12_TP/exercice_3/atrier/*.mp4)
LISTTXT=$(ls /home/perso/paiement/O12_TP/exercice_3/atrier/*.txt) 
for photo in $LISTPHOTOS
do 
  echo $photo
  cp $photo /home/etudiants/ybenjello021/photo
done


