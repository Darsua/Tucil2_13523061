#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image {
    int width, height, channels;
    unsigned char*** data;

public:
    explicit Image(const std::string& pathString); // Constructor
    ~Image(); // Destructor

    bool isLoaded() const; // Checks if the image is successfully loaded
    void save(const std::string& pathString) const; // Saves the image to a file

    int getWidth() const; // Returns the width of the image
    int getHeight() const; // Returns the height of the image
    int getChannels() const; // Returns the number of channels in the image

    double* getMean(int x1, int y1, int x2, int y2) const; // Returns the mean of pixel values in a region
    double getVariance(int x1, int y1, int x2, int y2) const; // Returns the variance of pixel values in a region
    void normalize(int x1, int y1, int x2, int y2) const; // Normalizes pixel values in a region
};

#endif // IMAGE_H