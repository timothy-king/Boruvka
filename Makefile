FLAGS = -09 -Wall

all : mst

mst : main.o unionfind.o edge.o shrinkingset.o
	gcc ${FLAGS} main.o unionfind.o edge.o shrinkingset.o -o mst

unionfind.o : node.h unionfind.h unionfind.c
	gcc ${FLAGS} -c unionfind.c

edge.o : edge.h node.h edge.c
	gcc ${FLAGS} -c edge.c

shrinkingset.o : shrinkingset.h shrinkingset.c
	gcc ${FLAGS} -c shrinkingset.c

main.o : unionfind.h edge.h main.c
	gcc ${FLAGS} -c main.c

clean :
	rm *.o
	rm mst