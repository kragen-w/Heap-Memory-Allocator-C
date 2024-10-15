mallocTest: mallocTest.o duMalloc.o
	gcc mallocTest.o duMalloc.o -o mallocTest

# what can effect this? what is included in this? what gets pasted?
mallocTest.o: mallocTest.c dumalloc.h
	gcc mallocTest.c -c

duMalloc.o: duMalloc.c dumalloc.h
	gcc duMalloc.c -c

clean:
	rm -f *.o
	rm -f mallocTest
# this just removes all dat shit, -f gets rid of any warning

# gcc mallocTest.c -MM gives you all of the things that it takes to make mallocTest.c