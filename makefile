CC=g++
EXE_FILE=a.out

all: $(EXE_FILE)

$(EXE_FILE): econdata.cpp econdata.hpp explore_econdata.cpp
	$(CC) econdata.cpp explore_econdata.cpp -o $(EXE_FILE)

econ_source.o: econdata.hpp explore_econdata.cpp
	$(CC) -c explore_econdata.cpp

clean:
	rm -f *.o $(EXE_FILE)
