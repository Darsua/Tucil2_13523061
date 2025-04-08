#ifndef QUADTREE_H
#define QUADTREE_H

#include "Image.h"

class Quadtree {
    int x1, y1, x2, y2;
    Quadtree* children[4] = {};

    static int method;
    static int threshold;
    static int minBlockSize;
    static Image* image;

public:
    Quadtree(int x1, int y1, int x2, int y2); // Constructor
    ~Quadtree(); // Destructor

    double getError() const; // Calculates the error for the current node with the given method
    static void setMethod(int m); // Sets the method for error calculation
    static void setImage(Image& img); // Sets the image for the quadtree
    static void setThreshold(int value); // Sets the threshold value
    static void setMinBlockSize(int size); // Sets the minimum block size
    static void Compress(); // Starts the compression process
};

#endif // QUADTREE_H