all: main_process command province city store

main_process: main_process.o
	g++ -std=c++11 main_process.o -o StoreCalculator.out

main_process.o: main_process.cpp
	g++ -std=c++11 -c main_process.cpp

command: command.o
	g++ -std=c++11 command.o -o command

command.o: command.cpp
	g++ -std=c++11 -c command.cpp

province: province.o
	g++ -std=c++11 province.o -o province
province.o: province.cpp
	g++ -std=c++11 -c province.cpp

city: city.o
	g++ -std=c++11 city.o -o city
city.o: city.cpp
	g++ -std=c++11 -c city.cpp

store: store.o
	g++ -std=c++11 store.o -o store
store.o: store.cpp
	g++ -std=c++11 -c store.cpp



.PHONY: clean

clean:
	rm *.o 
	rm StoreCalculator.out
	rm command
	rm province
	rm city
	rm store