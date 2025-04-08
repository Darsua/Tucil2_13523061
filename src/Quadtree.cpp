#include "Quadtree.h"

using namespace std;

int Quadtree::minBlockSize = 2;
int Quadtree::threshold = 0;
Image* Quadtree::image = nullptr;

Quadtree::Quadtree(const int x1, const int y1, const int x2, const int y2) : x1(x1), y1(y1), x2(x2), y2(y2) { // NOLINT(*-no-recursion)

    if (image->getVariance(x1, y1, x2, y2) > threshold && (x2 - x1) * (y2 - y1) > minBlockSize) {
        const int midX = (x1 + x2) / 2;
        const int midY = (y1 + y2) / 2;

        children[0] = new Quadtree(x1, y1, midX, midY);
        children[1] = new Quadtree(midX, y1, x2, midY);
        children[2] = new Quadtree(x1, midY, midX, y2);
        children[3] = new Quadtree(midX, midY, x2, y2);
    }
    else {
        image->normalize(x1, y1, x2, y2);
    }
}

Quadtree::~Quadtree() {
    for (auto & i : children) {
        delete i;
    }
}

void Quadtree::setImage(Image& img) {
    image = &img;
}

void Quadtree::setThreshold(const int t) {
    threshold = t;
}

void Quadtree::setMinBlockSize(const int m) {
    minBlockSize = m;
}

void Quadtree::Compress() {
    Quadtree compressor(0, 0, image->getWidth() - 1, image->getHeight() - 1);
}



