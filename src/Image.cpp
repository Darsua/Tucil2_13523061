#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

class Image {
    int width, height, channels;
    unsigned char*** data;

public:
    Image() : width(0), height(0), channels(0), data(nullptr) {} // Default constructor

    explicit Image(const string &pathString): width(0), height(0), channels(0) { // Parameterized constructor
        // Convert string to char* (stbi_load requires char*)
        char* path = new char [pathString.length() + 1];
        strcpy(path, pathString.c_str());


        // Load the image (returns an unsigned char* to pixel data)
        unsigned char* rawImg = stbi_load(path, &width, &height, &channels, 0);
        delete[] path;

        // Check if the image was loaded successfully
        if (rawImg == nullptr) {return;} // If loading fails, return

        // Allocate memory for the image data
        data = new unsigned char**[height];
        for (int i = 0; i < height; ++i) {
            data[i] = new unsigned char*[width];
            for (int j = 0; j < width; ++j) {
                data[i][j] = new unsigned char[channels];
            }
        }

        // Copy the pixel data
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    data[i][j][k] = rawImg[(i * width + j) * channels + k];
                }
            }
        }

        // Free the raw image data
        stbi_image_free(rawImg);
    }

    ~Image() { // Destructor
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

    void printResolution() const {
        cout << "Resolution: " << width << "x" << height << endl;
    }

    void printPixel(const int x, const int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            cout << "Pixel coordinates out of bounds!" << endl;
            return;
        }

        cout << "Pixel at (" << x << ", " << y << "): ";
        for (int k = 0; k < channels; ++k) {
            cout << static_cast<int>(data[y][x][k]) << " ";
        }
        cout << endl;
    }

    bool isLoaded() const {
        return data != nullptr;
    }
};
