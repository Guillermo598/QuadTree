#include <iostream> 
#include "QuadTree.h"

int main() {
	CImg<char> R;
	R.load("monalisa.png");
	R.display();

	QuadTree qt;
	qt.build("monalisa.png");
	qt.draw();
	qt.compress("monalisa.bin");

	QuadTree qt2;
	qt2.load("monalisa.bin");
	qt2.draw();
	
	return 0;


}
