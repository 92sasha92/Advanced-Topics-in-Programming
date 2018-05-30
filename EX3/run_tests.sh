#!/bin/bash
err[55]=0
counter=0
for ((i=1; i<=55; i++ ))
do
    echo ""
    echo ""
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "TEST_$i:"
    echo ""
    echo ""

    cp "./tests/test_$i/player1.rps_board" "./player1.rps_board"
    cp "./tests/test_$i/player2.rps_board" "./player2.rps_board"
    cp "./tests/test_$i/player1.rps_moves" "./player1.rps_moves"
    cp "./tests/test_$i/player2.rps_moves" "./player2.rps_moves"

    ./ex3 file-vs-file

    if diff ./rps.output ./tests/test_$i/rps.output; then
        echo PASS
    else
        let counter=counter+1
        echo FAIL
		err[$i]=$i 
    fi
done

echo ""
echo ""
echo ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
echo "$counter TESTS FAILED"
echo ""

for j in "${err[@]}" 
do
	if (("$j" != 0))
	then
		echo "Test_Failed_"$j
	fi
done

echo ""

