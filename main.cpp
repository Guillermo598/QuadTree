#include <iostream> 
#include "QuadTree.h"

int main() {
	string imagen = "cara.jpg";
	CImg<float> img;
	img.load(imagen.c_str());
	QuadTree qt, nqt;
	qt.build(imagen);
	qt.draw();

	qt.compress("cara.bin");
	nqt.load("cara.bin");
	nqt.draw();
	return 0;

}
