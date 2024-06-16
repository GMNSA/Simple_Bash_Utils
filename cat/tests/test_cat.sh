#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="bytes.txt"
TEST_RESULT="result.txt"
TEST_LOG="log.txt"
echo "" > log.txt

function remove_tmp_files() {
	if [ -e $TEST_RESULT ]; then
		rm $TEST_RESULT;
	fi
}

# function for show anmation

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

function test1() {
    for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
    do
        TEST1="$var $TEST_FILE"
        ./f_cat $TEST1 > f_cat.txt
        cat $TEST1 > cat.txt
        DIFF_RES="$(diff -s f_cat.txt cat.txt)"
        if [ "$DIFF_RES" == "Files f_cat.txt and cat.txt are identical" ]
        then
            # (( COUNTER_SUCCESS++ ))
            echo "SUCCESS" >> $TEST_RESULT
        else
            echo "$TEST1" >> $TEST_LOG
            # (( COUNTER_FAIL++ ))
            echo "FAIL" >> $TEST_RESULT
            echo "$TEST1"
        fi
        rm f_cat.txt cat.txt
    done
}

# -- -------------------------------------------- --

function test2() {
    for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
    do
        for var2 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
        do
            if [ $var != $var2 ]
            then
                TEST1="$var $var2 $TEST_FILE"
                ./f_cat $TEST1 > f_cat.txt
                cat $TEST1 > cat.txt
                DIFF_RES="$(diff -s f_cat.txt cat.txt)"
                if [ "$DIFF_RES" == "Files f_cat.txt and cat.txt are identical" ]
                then
                    # (( COUNTER_SUCCESS++ ))
                    echo "SUCCESS" >> $TEST_RESULT
                else
                    echo "$TEST1" >> $TEST_LOG
                    # (( COUNTER_FAIL++ ))
                    echo "FAIL" >> $TEST_RESULT
                    echo "$TEST1"
                fi
                rm f_cat.txt cat.txt
            fi
        done
    done
}

# -- -------------------------------------------- --

function test3() {
    for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
    do
        for var2 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
        do
            for var3 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
            do
                if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
                then
                    TEST1="$var $var2 $var3 $TEST_FILE"
                    ./f_cat $TEST1 > f_cat.txt
                    cat $TEST1 > cat.txt
                    DIFF_RES="$(diff -s f_cat.txt cat.txt)"
                    if [ "$DIFF_RES" == "Files f_cat.txt and cat.txt are identical" ]
                    then
                        # (( COUNTER_SUCCESS++ ))
                        echo "SUCCESS" >> $TEST_RESULT
                    else
                        echo "$TEST1" >> $TEST_LOG
                        # (( COUNTER_FAIL++ ))
                        echo "FAIL" >> $TEST_RESULT
                        echo "$TEST1"
                    fi
                    rm f_cat.txt cat.txt

                fi
            done
        done
    done
}

# -- -------------------------------------------- --

function test4() {
    for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
    do
        for var2 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
        do
            for var3 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
            do
                for var4 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
                do
                    if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                    then
                        TEST1="$var $var2 $var3 $var4 $TEST_FILE"
                        ./f_cat $TEST1 > f_cat.txt
                        cat $TEST1 > cat.txt
                        DIFF_RES="$(diff -s f_cat.txt cat.txt)"
                        if [ "$DIFF_RES" == "Files f_cat.txt and cat.txt are identical" ]
                        then
                            # (( COUNTER_SUCCESS++ ))
                            echo "SUCCESS" >> $TEST_RESULT
                        else
                            echo "$TEST1" >> $TEST_LOG
                            # (( COUNTER_FAIL++ ))
                            echo "FAIL" >> $TEST_RESULT
                            echo "$TEST1"
                        fi
                        rm f_cat.txt cat.txt

                    fi
                done
            done
        done
    done
}

# -- -------------------------------------------- --

remove_tmp_files

test1 &
test_pid=$!
show_loading_message $test_pid

test2 &
test_pid=$!
show_loading_message $test_pid

test3 &
test_pid=$!
show_loading_message $test_pid

test4 &
test_pid=$!
show_loading_message $test_pid


COUNTER_SUCCESS=$(grep -c "SUCCESS" $TEST_RESULT)
COUNTER_FAIL=$(grep -c "FAIL" $TEST_RESULT)

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
remove_tmp_files
