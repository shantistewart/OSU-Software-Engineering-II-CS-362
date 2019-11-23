CFLAGS= -Wall -fpic -coverage -lm -std=c99


rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player


baron_test: baron_test.c dominion.o rngs.o
	gcc -o baron_test -g baron_test.c dominion.o rngs.o $(CFLAGS)

minion_test: minion_test.c dominion.o rngs.o
	gcc -o minion_test -g minion_test.c dominion.o rngs.o $(CFLAGS)

ambassador_test: ambassador_test.c dominion.o rngs.o
	gcc -o ambassador_test -g ambassador_test.c dominion.o rngs.o $(CFLAGS)

mine_test: mine_test.c dominion.o rngs.o
	gcc -o mine_test -g mine_test.c dominion.o rngs.o $(CFLAGS)

unit_test_results: baron_test minion_test ambassador_test mine_test
	./baron_test >> unit_test_results.out
	./minion_test >> unit_test_results.out
	./ambassador_test >> unit_test_results.out
	./mine_test >> unit_test_results.out
	gcov -b -f dominion.c >> unit_test_results.out
	cat dominion.c.gcov >> unit_test_results.out


baron_random_test: randomtestcard1.c dominion.o rngs.o
	gcc -o baron_random_test -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

minion_random_test: randomtestcard2.c dominion.o rngs.o
	gcc -o minion_random_test -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

tribute_random_test: randomtestcard3.c dominion.o rngs.o
	gcc -o tribute_random_test -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)

randomtestresults: baron_random_test minion_random_test tribute_random_test
	./baron_random_test >> randomtestresults.out
	./minion_random_test >> randomtestresults.out
	./tribute_random_test >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f baron_test minion_test ambassador_test mine_test unit_test_results.out
	rm -f baron_random_test minion_random_test tribute_random_test randomtestresults.out
