#!/bin/sh

while :
do

    if ln ex2.txt ex2.txt.lock 
    then
        NUMBER=$(tail -n 1 < ex2.txt)
        let NUMBER=$NUMBER+1
        echo $NUMBER >> ex2.txt

        rm ex2.txt.lock
    fi

done
# the first race condition was number 653; it was printed 2 times at lines 653 and 654
# the critical region is the body of while loop: we access the text file there.
# what happens is 2 processes read the same number n, then print n+1