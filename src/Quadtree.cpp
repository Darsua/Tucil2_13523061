#include "Quadtree.h"

using namespace std;

int Quadtree::method = 0;
int Quadtree::minBlockSize = 2;
int Quadtree::threshold = 0;

Image* Quadtree::image = nullptr;
Gifs* Quadtree::gif = nullptr;

int Quadtree::maxDepth = 0;
int Quadtree::nodes = 0;

Quadtree::Quadtree(const int x1, const int y1, const int x2, const int y2, const int depth) : x1(x1), y1(y1), x2(x2), y2(y2) { // NOLINT(*-no-recursion)
    const double error = getError();

    if (error > threshold && (x2 - x1) * (y2 - y1) > minBlockSize) {
        const int midX = (x1 + x2) / 2;
        const int midY = (y1 + y2) / 2;

        children[0] = new Quadtree(x1, y1, midX, midY, depth + 1);
        children[1] = new Quadtree(midX, y1, x2, midY, depth + 1);
        children[2] = new Quadtree(x1, midY, midX, y2, depth + 1);
        children[3] = new Quadtree(midX, midY, x2, y2, depth + 1);
    }
    else {
        image->normalize(x1, y1, x2, y2);
        if (depth > maxDepth) {
            maxDepth = depth;
            gif->addFrame(*image);
        }
    }
    nodes++;
}

Quadtree::~Quadtree() {
    for (const auto & i : children) {
        delete i;
    }
}

double Quadtree::getError() const {
    switch (method) {
        case 1:
            return image->getVariance(x1, y1, x2, y2);
        case 2:
            return image->getMAD(x1, y1, x2, y2);
        case 3:
            return image->getMPD(x1, y1, x2, y2);
        case 4:
            return image->getEntropy(x1, y1, x2, y2);
        default:
            return 0;
    }
}

void Quadtree::setMethod(const int m) {
    method = m;
}

void Quadtree::setImage(Image& img) {
    image = &img;
}

void Quadtree::setGif(Gifs& g) {
    gif = &g;
}

void Quadtree::setThreshold(const int t) {
    threshold = t;
}

void Quadtree::setMinBlockSize(const int m) {
    minBlockSize = m;
}

void Quadtree::Compress() {
    Quadtree compressor(0, 0, image->getWidth() - 1, image->getHeight() - 1, 1);
}
