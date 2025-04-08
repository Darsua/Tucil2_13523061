#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <fstream>

class Image {
    int width, height, channels;
    unsigned char*** data;

public:
    static std::streamsize sizeBefore;
    static std::streamsize sizeAfter;

    explicit Image(const std::string& pathString); // Constructor
    Image(const Image&); // Copy constructor
    ~Image(); // Destructor
    Image& operator=(const Image&); // Dirty assignment operator

    bool isLoaded() const; // Checks if the image is successfully loaded
    void save(const std::string& pathString) const; // Saves the image to a file
    static std::streamsize getFileSize(const std::string& filename); // Returns the size of the file

    int getWidth() const; // Returns the width of the image
    int getHeight() const; // Returns the height of the image

    double* getMean(int x1, int y1, int x2, int y2) const; // Returns the mean of pixel values in a region
    double getVariance(int x1, int y1, int x2, int y2) const; // Returns the variance of pixel values in a region
    double getMAD(int x1, int y1, int x2, int y2) const; // Returns the mean absolute deviation of pixel values in a region
    double getMPD(int x1, int y1, int x2, int y2) const; // Returns the max pixel difference of pixel values in a region
    double getEntropy(int x1, int y1, int x2, int y2) const; // Returns the entropy of pixel values in a region

    void normalize(int x1, int y1, int x2, int y2) const; // Normalizes pixel values in a region
};

#endif // IMAGE_H