#!/bin/bash
counter=0
for ((i=1; i<=40; i++ ))
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

    ./ex1

    if diff ./rps.output ./tests/test_$i/rps.output; then
        echo PASS
    else
        let counter=counter+1
        echo FAIL
    fi
done

echo ""
echo ""
echo ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
echo "$counter TESTS FAILED"
