
testme: testme.c
	gcc -o testme testme.c -coverage -fpic -lm
	./testme
	gcov testme.c -b

clean:
	rm testme
	rm testme.gcda
	rm testme.gcno
	rm testme.c.gcov
