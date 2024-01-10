bin/testBSTree: BSTree.h BSNode.h testBSTree.cpp
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp

bin/testBSTreeDict: BSTreeDict.h BSTree.h testBSTreeDict.cpp
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp

clean:
	rm -rf *.o *.gch bin
