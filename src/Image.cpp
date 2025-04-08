#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>

using namespace std;

Image::Image(const string &pathString): width(0), height(0), channels(0) // Parameterized constructor
{
    // Convert string to char* (stbi_load requires char*)
    char* path = new char [pathString.length() + 1];
    strcpy(path, pathString.c_str());

    // Load the image (returns an unsigned char* to pixel data)
    unsigned char* rawImg = stbi_load(path, &width, &height, &channels, 0);
    delete[] path;

    // Check if the image was loaded successfully
    if (rawImg == nullptr) {
        return;
    } // If loading fails, return

    // Allocate memory for the image data
    data = new unsigned char**[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new unsigned char*[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = new unsigned char[channels];
        }
    }

    // Copy the pixel data
    for (int i = 0; i < height; ++i) {for (int j = 0; j < width; ++j) {
        for (int k = 0; k < channels; ++k) {
            data[i][j][k] = rawImg[(i * width + j) * channels + k];
            }
        }
    }

    // Free the raw image data
    stbi_image_free(rawImg);
}

Image::~Image() { // Destructor
    if (data) {
        for (int i = 0; i < height; ++i) {
            if (data[i]) {
                for (int j = 0; j < width; ++j) {
                    delete[] data[i][j];
                }
                delete[] data[i];
            }
        }
        delete[] data;
    }
}

bool Image::isLoaded() const {
    return data != nullptr && width > 0 && height > 0 && channels > 0;
}

void Image::save(const string &pathString) const {
    // Convert string to char* (stbi_write_png requires char*)
    char* path = new char[pathString.length() + 1];
    strcpy(path, pathString.c_str());

    // Revert the image data to a single array for saving
    auto* rawImg = new unsigned char[width * height * channels];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < channels; ++k) {
                rawImg[(i * width + j) * channels + k] = data[i][j][k];
            }
        }
    }

    stbi_write_png(path, width, height, channels, rawImg, width * channels);

    cout << "Image saved to " << pathString << endl;
    delete[] path;
    delete[] rawImg;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

double* Image::getMean(const int x1, const int y1, const int x2, const int y2) const {
    auto* mean = new double[channels];
    for (int k = 0; k < channels; ++k) {
        mean[k] = 0;
    }

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            for (int k = 0; k < channels; ++k) {
                mean[k] += data[i][j][k];
            }
        }
    }

    for (int k = 0; k < channels; ++k) {
        mean[k] /= (x2 - x1 + 1) * (y2 - y1 + 1);
    }

    return mean;
}

double Image::getVariance(const int x1, const int y1, const int x2, const int y2) const {
    const double* mean = getMean(x1, y1, x2, y2);

    auto* variances = new double[channels];
    for (int k = 0; k < channels; ++k) {
        variances[k] = 0;
    }

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            for (int k = 0; k < channels; ++k) {
                const double diff = data[i][j][k] - mean[k];
                variances[k] += diff * diff;
            }
        }
    }

    for (int k = 0; k < channels; ++k) {
        variances[k] /= (x2 - x1 + 1) * (y2 - y1 + 1);
    }

    double variance = 0;
    for (int k = 0; k < channels; ++k) {
        variance += variances[k];
    }

    delete[] mean;
    delete[] variances;

    return variance / channels;
}

double Image::getMAD(const int x1, const int y1, const int x2, const int y2) const {
    const double* mean = getMean(x1, y1, x2, y2);

    auto* deviations = new double[channels];
    for (int k = 0; k < channels; ++k) {
        deviations[k] = 0;
    }

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            for (int k = 0; k < channels; ++k) {
                deviations[k] += abs(data[i][j][k] - mean[k]) ;
            }
        }
    }

    for (int k = 0; k < channels; ++k) {
        deviations[k] /= (x2 - x1 + 1) * (y2 - y1 + 1);
    }

    double deviation = 0;
    for (int k = 0; k < channels; ++k) {
        deviation += deviations[k];
    }

    delete[] mean;
    delete[] deviations;

    return deviation / channels;
}

double Image::getMPD(const int x1, const int y1, const int x2, const int y2) const {
    int* maxes = new int[channels];
    int* mins = new int[channels];

    for (int k = 0; k < channels; ++k) {
        maxes[k] = 0;
        mins[k] = 255;
    }

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            for (int k = 0; k < channels; ++k) {
                if (data[i][j][k] > maxes[k]) {
                    maxes[k] = data[i][j][k];
                }
                if (data[i][j][k] < mins[k]) {
                    mins[k] = data[i][j][k];
                }
            }
        }
    }

    double diff = 0;
    for (int k = 0; k < channels; ++k) {
        diff += maxes[k] - mins[k];
    }

    delete[] maxes;
    delete[] mins;

    return diff / channels;
}

double Image::getEntropy(const int x1, const int y1, const int x2, const int y2) const {
    int **histograms = new int*[channels];
    for (int k = 0; k < channels; ++k) {
        histograms[k] = new int[256]{0};
    }

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            for (int k = 0; k < channels; ++k) {
                histograms[k][data[i][j][k]]++;
            }
        }
    }

    auto* entropies = new double[channels];
    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;
    for (int k = 0; k < channels; ++k) {
        entropies[k] = 0;
        for (int i = 0; i < 256; ++i) {
            if (histograms[k][i] > 0) {
                double p = static_cast<double>(histograms[k][i]) / (width * height);
                entropies[k] -= p * log2(p);
            }
        }
    }

    double entropy = 0;
    for (int k = 0; k < channels; ++k) {
        entropy += entropies[k];
    }

    delete[] entropies;
    for (int k = 0; k < channels; ++k) {
        delete[] histograms[k];
    }
    delete[] histograms;

    return entropy / channels;
}

void Image::normalize(const int x1, const int y1, const int x2, const int y2) const {
    const double* mean = getMean(x1, y1, x2, y2);

    for (int i = y1; i <= y2; ++i) {
        for (int j = x1; j <= x2; ++j) {
            for (int k = 0; k < channels; ++k) {
                data[i][j][k] = static_cast<unsigned char>(mean[k]);
            }
        }
    }
    delete[] mean;
}
