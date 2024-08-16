output: main.o BSTree.o AVLTree.o LLRBTree.o
	g++ -std=c++11 main.o BSTree.o AVLTree.o LLRBTree.o -o webstore

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

BSTree.o: BSTree.cpp
	g++ -std=c++11 -c BSTree.cpp

AVLTree.o: AVLTree.cpp
	g++ -std=c++11 -c AVLTree.cpp

LLRBTree.o: LLRBTree.cpp
	g++ -std=c++11 -c LLRBTree.cpp

clean:
	rm *.o