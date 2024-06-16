#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_RESULT="result.txt"
TEST_LOG="log.txt"
echo "" > log.txt

function show_loading_message() {
    local pid=$1
    local delay=0.1
    local spinstr='|/-\'
    local temp

    echo -n "Running tests... "
    while kill -0 $pid 2>/dev/null; do
        temp=${spinstr#?}
        printf " [%c]  " "$spinstr"
        spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b"
    done
    echo "Done"
}

# -- -------------------------------------------- --

function remove_tmp_files() {
    if [ -e $TEST_RESULT ]; then
        rm $TEST_RESULT;
    fi
}

# -- -------------------------------------------- --

function test1() {
    for var in -v -c -l -n -h -o -i
    do
        for var2 in -v -c -l -n -h -o -i
        do
            for var3 in -v -c -l -n -h -i -o
            do
                if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
                then
                    TEST1="for ../srcs/f_grep.c ../Makefile $var $var2 $var3"
                    ../f_grep $TEST1 > f_grep.txt
                    grep $TEST1 > grep.txt
                    DIFF_RES="$(diff -s f_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files f_grep.txt and grep.txt are identical" ]
                    then
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST1" >> $TEST_LOG
                        echo "FAIL" >> $TEST_RESULT
                    fi
                    rm f_grep.txt grep.txt

                    TEST2="for ../srcs/f_grep.c $var $var2 $var3"
                    ../f_grep $TEST2 > f_grep.txt
                    grep $TEST2 > grep.txt
                    DIFF_RES="$(diff -s f_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files f_grep.txt and grep.txt are identical" ]
                    then
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST2" >> $TEST_LOG
                        echo "FAIL" >> $TEST_RESULT
                    fi
                    rm f_grep.txt grep.txt

                    TEST3="-e for -e ^int ../srcs/f_grep.c ../Makefile $var $var2 $var3"
                    ../f_grep $TEST3 > f_grep.txt
                    grep $TEST3 > grep.txt
                    DIFF_RES="$(diff -s f_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files f_grep.txt and grep.txt are identical" ]
                    then
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST3" >> $TEST_LOG
                        echo "FAIL" >> $TEST_RESULT
                    fi
                    rm f_grep.txt grep.txt

                    TEST4="-e for -e ^int ../srcs/f_grep.c $var $var2 $var3"
                    ../f_grep $TEST4 > f_grep.txt
                    grep $TEST4 > grep.txt
                    DIFF_RES="$(diff -s f_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files f_grep.txt and grep.txt are identical" ]
                    then
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST4" >> $TEST_LOG
                        echo "FAIL" >> $TEST_RESULT
                    fi
                    rm f_grep.txt grep.txt

                    TEST5="-e regex -e ^print ../srcs/f_grep.c $var $var2 $var3 -f ./pattern.txt"
                    ../f_grep $TEST5 > f_grep.txt
                    grep $TEST5 > grep.txt
                    DIFF_RES="$(diff -s f_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files f_grep.txt and grep.txt are identical" ]
                    then
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST5" >> $TEST_LOG
                        echo "FAIL" >> $TEST_RESULT
                    fi
                    rm f_grep.txt grep.txt

                    TEST6="-e while -e void ../srcs/f_grep.c ../Makefile $var $var2 $var3 -f ./pattern.txt"
                    ../f_grep $TEST6 > f_grep.txt
                    grep $TEST6 > grep.txt
                    DIFF_RES="$(diff -s f_grep.txt grep.txt)"
                    if [ "$DIFF_RES" == "Files f_grep.txt and grep.txt are identical" ]
                    then
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST6"
                        echo "$TEST6" >> $TEST_LOG
                        echo "FAIL" >> $TEST_RESULT
                    fi
                    rm f_grep.txt grep.txt
                fi
            done
        done
    done
}

# -- -------------------------------------------- --

test1 &
test_pid=$!
show_loading_message $test_pid

COUNTER_SUCCESS=$(grep -c "SUCCESS" $TEST_RESULT)
COUNTER_FAIL=$(grep -c "FAIL" $TEST_RESULT)

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
remove_tmp_files
