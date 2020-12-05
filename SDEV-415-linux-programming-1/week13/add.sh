#! /bin/bash

function add() {
    if [ "$#" -ne 2 ]; then
        echo "Illegal number of parameters. Run 'add.sh x y'"
        return
    fi
    sum=$(($1+$2))
    echo "The sum of $1 and $2 is $sum" 
}

add $1 $2