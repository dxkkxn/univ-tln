DATE=$(date +%Y%m%d)
LOG=$(find /home/perso/paiement/O12_TP/exercice_4/nontraite -name $DATE*.log) 
mkdir /home/etudiants/ybenjello021/archive
mkdir /home/etudiants/ybenjello021/archive/$DATE
mkdir /home/etudiants/ybenjello021/archive/$DATE/log
mkdir /home/etudiants/ybenjello021/archive/$DATE/err
cp= $LOG /home/etudiants/ybenjello021/archive/$DATE/log
cp= $ERR /home/etudiants/ybenjello021/archive/$DATE/err
