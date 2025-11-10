bin/testListLinked: testListLinked.cpp ListLinked.h Node.h List.h
		mkdir -p bin
		g++ -std=c++17 -o bin/testListLinked testListLinked.cpp


clean:
	 rm -rf *.o *.gch bin
