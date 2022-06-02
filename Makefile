all: libmy_complex.so complex_02
clean:
	rm complex_02 complex_02.o libmy_complex.so

complex_02: complex_02.o
	g++ complex_02.o libmy_complex.so -o complex_02 `pkg-config --libs gtk+-3.0` -lpthread

complex_02.o: complex_02.cpp
	g++ -c complex_02.cpp -o complex_02.o `pkg-config --cflags gtk+-3.0` 

libmy_complex.so: libmy_complex.cpp my_complex.h
	g++ -shared -c libmy_complex.cpp -o libmy_complex.so
