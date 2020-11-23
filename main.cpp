#include <iostream> 
#include "QuadTree.h"

int main() {
	string imagen = "cara.jpg";
	CImg<float> img;
	img.load(imagen.c_str());
	img.display();

	QuadTree qt;
	qt.build(imagen);
	qt.draw();
	qt.compress("cara.bin");
		
	QuadTree qt2;
	qt2.load("cara.bin");
	qt2.draw();
	return 0;

}
