#!/bin/bash
# Liste les commandes internes et externes
#while read aux cmd reste
#do
#    echo aux=$aux cmd=$cmd
##done < /tmp/bidon.txt
#done < <( tr ':' ' ' < /etc/passwd )

while read aux cmd
do
    if which $cmd > /dev/null; then
        echo $cmd
    fi
done < <( enable )
