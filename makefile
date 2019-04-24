OBJS=dtree.o id3.o
CC=g++
PROGRAM=./dtree
CFLAGS=-std=c++11
INDIR=./inputs/

ALG=E

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)

iris: $(PROGRAM)
	$(PROGRAM) $(INDIR)iris.csv
	
restaurant: $(PROGRAM)
	$(PROGRAM) $(INDIR)restaurant.csv
	
weather: $(PROGRAM)
	$(PROGRAM) $(INDIR)weather.csv