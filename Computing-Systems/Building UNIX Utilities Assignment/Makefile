p1: wunzip.o wgrep.o wzip.o wcat.o
	g++ -o wunzip wunzip.o
	g++ -o wgrep wgrep.o
	g++ -o wzip wzip.o
	g++ -o wcat wcat.o

wunzip.o: wunzip.cpp
	g++ -c wunzip.cpp

wcat.o: wcat.cpp
	g++ -c wcat.cpp

wgrep.o: wgrep.cpp
	g++ -c wgrep.cpp

wzip.o: wzip.cpp
	g++ -c wzip.cpp

clean:
	rm -rf *.o p1

