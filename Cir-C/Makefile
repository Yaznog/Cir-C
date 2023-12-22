CFLAGS=-g

all : Cir-C

Cir-C :  Cir-C.o
	g++ -o main $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ Cir-C
