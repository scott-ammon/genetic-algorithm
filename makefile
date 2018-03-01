proj5: randNumbers.o ChromosomeClass.o GeneticAlgorithmClass.o ParameterClass.o resistanceFunction.o main5.o
	g++ -g randNumbers.o ChromosomeClass.o GeneticAlgorithmClass.o ParameterClass.o resistanceFunction.o main5.o -o proj5

randNumbers.o: randNumbers.cpp
	g++ -c randNumbers.cpp -o randNumbers.o

ChromosomeClass.o: ChromosomeClass.cpp GeneClass.h GlobalConstants.h
	g++ -c ChromosomeClass.cpp -o ChromosomeClass.o

GeneticAlgorithmClass.o: GeneticAlgorithmClass.cpp
	g++ -c GeneticAlgorithmClass.cpp -o GeneticAlgorithmClass.o

ParameterClass.o: ParameterClass.cpp
	g++ -c ParameterClass.cpp -o ParameterClass.o

resistanceFunction.o: resistanceFunction.cpp
	g++ -c resistanceFunction.cpp -o resistanceFunction.o

main5.o: main5.cpp
	g++ -c main5.cpp -o main5.o

clean:
	rm -rf *.o proj5

