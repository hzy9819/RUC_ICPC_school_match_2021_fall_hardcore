CC:=g++
src:=route
data:=data_maker

exe:
	$(CC) -o $(src) $(src).cpp Hypergraph.cpp
	$(CC) -o $(data) $(data).cpp

debug:
	$(CC) -o $(src) $(src).cpp Hypergraph.cpp -g -Wall
	$(CC) -o $(data) $(data).cpp -g -Wall

clean: 
	rm -f $(src) $(data)

clean_data:
	rm -f *.in *.out

$(src):$(src).cpp Hypergraph.cpp
	$(CC) -o $(src) $(src).cpp Hypergraph.cpp
$(data):$(data).cpp
	$(CC) -o $(data) $(data).cpp


data:$(src) $(data)
	./$(data)
	./$(src) $(src)0.in $(src)0.out
	./$(src) $(src)1.in $(src)1.out
	./$(src) $(src)2.in $(src)2.out
