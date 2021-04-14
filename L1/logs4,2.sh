if ["$1" = ""]
then
DATE=$(date +%Y%m%d)
else
DATE="$1"
fi 
mkdir /home/etudiants/ybenjello021/archive/$DATE
mkdir /home/etudiants/ybenjello021/archive/$DATE/log
mkdir /home/etudiants/ybenjello021/archive/$DATE/err
cp /home/perso/paiement/O12_TP/exercice_4/nontraite/$DATE*.log /home/etudiants/ybenjello021/archive/$DATE/log
cp /home/perso/paiement/O12_TP/exercice_4/nontraite/$DATE*.err /home/etudiants/ybenjello021/archive/$DATE/err
