CC:=g++
src:=ba_king
data:=data_maker

exe:
	$(CC) -o $(src) $(src).cpp -O2
	$(CC) -o $(data) $(data).cpp -O2

debug:
	$(CC) -o $(src) $(src).cpp -g -Wall
	$(CC) -o $(data) $(data).cpp -g -Wall

clean: 
	rm -f $(src) $(data)

clean_data:
	rm -f *.in *.out

$(src):$(src).cpp 
	$(CC) -o $(src) $(src).cpp -O2
$(data):$(data).cpp
	$(CC) -o $(data) $(data).cpp -O2

data:$(src) $(data)
	./$(data)
	./$(src) $(src)0.in $(src)0.out
	./$(src) $(src)1.in $(src)1.out
	./$(src) $(src)2.in $(src)2.out
	./$(src) $(src)3.in $(src)3.out
	./$(src) $(src)4.in $(src)4.out