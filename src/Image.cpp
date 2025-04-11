#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

streamsize Image::sizeBefore = 0;
streamsize Image::sizeAfter = 0;

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

    // Allocate memory for the sum table
    sumTable = new long long**[height];
    for (int i = 0; i < height; ++i) {
        sumTable[i] = new long long*[width];
        for (int j = 0; j < width; ++j) {
            sumTable[i][j] = new long long[channels];
            for (int k = 0; k < channels; ++k) {
                sumTable[i][j][k] = 0;
            }
        }
    }

    // Fill the image data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < channels; ++k) {
                // Fill out the image data
                data[i][j][k] = rawImg[(i * width + j) * channels + k];

                // Fill out the Sum Table
                sumTable[i][j][k] = data[i][j][k];
                if (i > 0) { sumTable[i][j][k] += sumTable[i - 1][j][k]; }
                if (j > 0) { sumTable[i][j][k] += sumTable[i][j - 1][k]; }
                if (i > 0 && j > 0) { sumTable[i][j][k] -= sumTable[i - 1][j - 1][k]; }
            }
        }
    }

    // Free the raw image data
    stbi_image_free(rawImg);

    // Note the size of the image before compression
    sizeBefore = getFileSize(pathString);
}

Image::Image(const Image &img) : width(img.width), height(img.height), channels(img.channels) // Copy constructor
{
    // Allocate memory for the image data
    data = new unsigned char**[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new unsigned char*[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = new unsigned char[channels];
        }
    }

    // Allocate memory for the sum table
    sumTable = new long long**[height];
    for (int i = 0; i < height; ++i) {
        sumTable[i] = new long long*[width];
        for (int j = 0; j < width; ++j) {
            sumTable[i][j] = new long long[channels];
            for (int k = 0; k < channels; ++k) {
                sumTable[i][j][k] = 0;
            }
        }
    }

    // Copy the Image data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < channels; ++k) {
                data[i][j][k] = img.data[i][j][k];
                sumTable[i][j][k] = img.sumTable[i][j][k];
            }
        }
    }
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

Image& Image::operator=(const Image &img) { // Dirty assignment operator
    if (this != &img & this->width == img.width && this->height == img.height && this->channels == img.channels) {
        // Copy pixel data
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    data[i][j][k] = img.data[i][j][k];
                }
            }
        }
    }
    return *this;
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

    delete[] path;
    delete[] rawImg;

    // Note the size of the image after compression
    sizeAfter = getFileSize(pathString);
}

streamsize Image::getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    return file.tellg();
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

double* Image::getMean(const int x1, const int y1, const int x2, const int y2) const {
    auto* mean = new double[channels];
    const int area = (x2 - x1 + 1) * (y2 - y1 + 1);

    for (int k = 0; k < channels; k++) {
        long long sum = sumTable[y2][x2][k];
        if (x1 > 0) sum -= sumTable[y2][x1 - 1][k];
        if (y1 > 0) sum -= sumTable[y1 - 1][x2][k];
        if (x1 > 0 && y1 > 0) sum += sumTable[y1 - 1][x1 - 1][k];

        mean[k] = static_cast<double>(sum) / area;
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
    const int width = x2 - x1 + 1;
    const int height = y2 - y1 + 1;
    for (int k = 0; k < channels; ++k) {
        entropies[k] = 0;
        for (int i = 0; i < 256; ++i) {
            if (histograms[k][i] > 0) {
                const double p = static_cast<double>(histograms[k][i]) / (width * height);
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
