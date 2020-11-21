#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include <string>
#include <vector>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

CImg<char>  Binarizar(CImg<float> & img, int umbral)
{
    CImg<char> R(img.width(),img.height());
    for(int i=0;i< img.width();i++)
        for(int j=0;j< img.height();j++)
        {
            int r = img(i,j,0);
            int g = img(i,j,1);
            int b = img(i,j,2);
            if ( (r+g+b)/3  > umbral)
                R(i,j) = 255;
            else
                R(i,j) = 0;
        }
    return R;
}

struct Node {
    int xi, xf, yi, yf;

    char color[4] = {};
    Node* children[4] = {};

    Node(int xi, int xf, int yi, int yf) {
        this->xi = xi;
        this->xf = xf;
        this->yi = yi;
        this->yf = yf;
    }
};

class QuadTree {
private:
    Node* root;
public:
    QuadTree():root(0){};
    Node* getRoot() {return root;}
    void insert(int xi, int xf, int yi, int yf, CImg<char>& img, Node* &n) {
        n = new Node(xi, xf, yi, yf);

        char pixel = img(xi,yi);
        bool c = true;
        for (int i = xi; i <= xf/2; ++i) { // cuadrante0
            for (int j = yi; j < yf/2; ++j) {
                if (pixel != img(i,j)) {
                    n->color[0] = 100;
                    insert(xi, xf/2, yi, yf/2, img, n->children[0]);
                    i = xf/2;
                    c = false;
                    break;
                }
            }
        }
        if (c) n->color[0] = pixel;
        c = true;
        pixel = img((xf/2)+1,yi);
        for (int i = (xf/2)+1; i < xf; ++i) { // cuadrante1
            for (int j = yi; j <= yf/2; ++j) {
                if (pixel != img(i,j)) {
                    n->color[1] = 100;
                    insert((xf/2)+1, xf, yi, yf/2, img, n->children[1]);
                    i = xf;
                    c = false;
                    break;
                }
            }
        }
        if (c) n->color[1] = pixel;
        c = true;
        pixel = img(xi,yf/2);
        for (int i = xi; i < xf/2; ++i) { // cuadrante2
            for (int j = yf/2; j < yf; ++j) {
                if (pixel != img(i,j)) {
                    n->color[2] = 100;
                    insert(xi, xf/2, yf/2, yf, img, n->children[2]);
                    i = xf/2;
                    c = false;
                    break;
                }
            }
        }
        if (c) n->color[2] = pixel;
        c = true;
        pixel = img(xf/2,yf/2);
        for (int i = xf/2; i < xf; ++i) { // cuadrante3
            for (int j = yf/2; j < yf; ++j) {
                if (pixel != img(i,j)) {
                    n->color[3] = 100;
                    insert(xf/2, xf, yf/2, yf, img, n->children[3]);
                    i = xf;
                    c = false;
                    break;
                }
            }
        }
        if (c) n->color[2] = pixel;
    }

    void build(string name) {
        CImg<float>   A(name);
        CImg<char>   R = Binarizar(A,40);


        insert(0,0, R.width(), R.height(), R, root);

        A.display();
        R.display();
    }

};


#endif //QUADTREE_QUADTREE_H
