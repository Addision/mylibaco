#!bin/sh

g++ -g -O2  ./libaco/aco.c ./libaco/aco.h ./libaco/aco_assert_override.h test_co2.cpp ./libaco/acosw.S Coroutine.h Coroutine.cpp -o test_co
