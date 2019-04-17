OBJS=dtree.o
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
	$(PROGRAM) $(ALG) < $(INDIR)iris.csv
	
restaurant: $(PROGRAM)
	$(PROGRAM) $(ALG) < $(INDIR)restaurant.csv
	
weather: $(PROGRAM)
	$(PROGRAM) $(ALG) < $(INDIR)weather.csv