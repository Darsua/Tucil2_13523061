#ifndef GIFS_H
#define GIFS_H

#include "gif.h"
#include "Image.h"
#include <string>

using namespace std;

class Gifs {
  GifWriter writer;

  public:
    Gifs(const string& pathString, const Image &image, const int delay = 10): writer({}) {
        GifBegin(&writer, pathString.c_str(), image.getWidth(), image.getHeight(), delay);
    }

    void addFrame(const Image &image, const int delay = 10) {
        const unsigned char* rawImg = image.getData();
        GifWriteFrame(&writer, rawImg, image.getWidth(), image.getHeight(), delay);
    }

    void finish() {
        GifEnd(&writer);
    }
};



#endif //GIFS_H
