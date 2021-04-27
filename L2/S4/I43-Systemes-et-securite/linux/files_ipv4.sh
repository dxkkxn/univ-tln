#!/bin/bash

for file in $( find /etc 2>/dev/null )
do
    if [ -f $file ]; then
        if  grep -Eq '([0-9]{1,3}\.){3}[0-9]{1,3}' $file 2>/dev/null
            then echo $file toto
        fi
    fi
done

