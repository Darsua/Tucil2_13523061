#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include <chrono>

#include "Image.h"
#include "Quadtree.h"

using namespace std;

void miku()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    cout <<u8R"(⠀⠀⠀⣠⡤⠤⠤⠤⣤⣤⣤⣤⣤⣤⣄⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⢀⡼⠋⠀⠄⣀⣾⣿⣿⣿⣿⣿⣟⡁⠈⠈⠉⠉⠙⠒⠶⠤⢄⣀⠀⠀⣠⣤⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⡞⠀⠐⠀⣴⣿⣿⣿⣿⡿⠟⠋⠁⠠⠈⡀⠡⠈⠄⠂⡀⠄⢀⠈⠙⠺⢿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⡇⠀⣡⣾⣿⣿⣿⠟⠉⠀⠄⠐⠈⡀⠐⡀⠂⠁⠄⢂⠠⠐⠀⡀⢦⡀⠀⠙⢿⣿⣿⡍⠳⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣇⣴⣿⣿⣿⠟⠁⢀⠈⠄⠂⡈⠐⡀⠡⠀⠡⢈⠀⠂⠄⠂⢁⠀⠸⣗⠈⢀⠀⠻⣿⣧⠀⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣿⣿⣿⣿⠁⠀⠐⠀⠀⠂⠐⠀⠁⡄⠂⠁⠐⠀⡌⠐⢠⠁⠀⠂⠀⣯⠀⠀⠂⠀⢹⣿⠀⢸⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣿⣿⡟⠁⠀⠌⢀⠂⢁⠈⠄⠁⠂⠄⠐⠈⡀⢁⠠⠐⠀⠄⢁⠐⢈⡯⠀⠌⢀⠂⠀⢻⡆⠈⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣯⡏⠀⠠⠁⡀⢂⠀⠂⣄⡂⠁⢈⠀⠌⠀⠄⠠⠀⠂⢁⠀⢂⠀⣾⠃⢀⠂⠄⠠⠁⡀⢷⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⡟⠀⠠⠁⡐⠀⠠⠐⠀⠙⠿⣆⠀⢂⣠⣬⡴⣾⠆⠁⠠⠈⢀⣼⠏⠀⠄⠂⠈⠄⠐⢀⢸⡆⠘⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⡇⠂⠁⡀⠄⠂⣁⣠⣬⣴⣶⣟⠿⣋⠁⠀⣰⠏⠀⠠⠁⣰⡾⠹⡇⢀⠐⢈⠠⠈⠀⠄⠠⡇⠈⢷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⣇⣤⣦⠀⠠⣸⡿⣻⠟⠋⠛⢿⣧⠉⢠⡞⠁⡀⠐⣠⡶⠋⢀⣀⣿⡄⠀⠂⠠⢀⠁⡄⡀⡇⢀⢺⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⢛⡇
⠀⣿⣿⣿⠘⢷⣿⢠⡏⠳⠦⣤⣼⠃⣼⣣⠤⠶⠖⢛⣽⣿⣭⣁⠀⣯⠀⠠⠁⡐⠀⢸⣧⠐⡇⠀⡈⣇⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣶⡖⣿⠉⠉⢳⣀⣠⣴⣾⣿⣿⣿⣿⢘⡇
⠀⣿⣿⣿⡀⢈⡟⠘⣦⡀⠄⣰⠏⠀⠀⠀⠀⠀⢀⡽⠛⠙⢺⡻⣇⡷⠀⡐⠀⠄⠈⣼⢻⢸⠃⠄⠀⣽⠀⣀⣠⣤⣴⣶⣾⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢘⡇
⠀⡟⣿⣿⣧⢘⡇⠀⠀⠉⠋⠁⠀⠀⠀⠀⠀⠀⣾⠙⠦⣤⢴⡇⣿⡏⠀⠄⠂⢈⢠⣏⣾⣾⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢨⡇
⠀⡇⠈⣿⠙⣯⣷⡀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⢿⣠⠀⣠⡞⢠⣿⠅⡀⠂⠈⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢨⡇
⠀⡇⠈⠹⢦⣈⡿⠙⣦⡀⠀⠈⠷⣀⣠⠀⠀⠀⠀⠉⠉⠁⢒⣿⡿⠀⠀⠂⢡⣿⣯⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢰⡇
⠀⡇⡐⠀⡈⣹⢿⣖⠠⠙⢦⣄⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣿⡟⠀⢀⣢⣼⣿⣿⣷⣏⠼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠰⡇
⠀⡇⠁⡀⢡⡟⠈⠙⠲⠦⣌⡿⢲⣤⠤⠤⠴⣖⢶⣾⣿⣿⠟⣁⣴⣾⣿⣿⣿⣿⣿⣿⠴⡹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣰⡇
⠀⡇⣰⠦⠿⠷⡤⣄⡀⠀⠀⠉⢻⣆⠀⠀⠀⢻⡜⣿⣿⣿⣿⣿⣿⣿⣷⣬⣭⣹⣍⣏⣳⣱⢣⡏⠙⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀
⠀⣷⠋⠀⠀⠀⠀⠀⠙⢷⢦⣀⢸⣇⣙⡷⢤⣀⣿⡘⣿⣿⣿⣿⣿⣿⠿⠟⣟⠉⣿⣿⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⡏⠀⠀⠀⠀⠀⠀⠀⠈⢷⣉⡿⠬⠿⠤⣤⣀⣀⠙⢻⡿⠟⠋⠉⠀⠀⠀⢸⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⢸⡅⡖⡄⢿⠀⠀⠀⠀⠀⠈⣻⣿⣿⣿⣷⣶⣦⣬⡙⠾⣄⠀⠀⠀⠀⠀⠀⢸⢼⣃⠉⢉⠋⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⡇⢧⡝⠸⠆⠀⠀⢸⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣬⣳⣄⠀⠀⠀⠀⢸⣾⣿⣿⣿⣿⣦⣀⠈⠻⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠉⠒⠢⢤⣀⠀⠀⠀⠀
⠀⡇⠀⠀⠀⠀⠀⠀⠈⣇⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠉⠷⣄⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡗⠦⢄⣀⠀⠉⠑⠲⡆
⠀⣿⠀⠀⣀⣠⡤⠶⣚⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣶⡀⠙⢧⡄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⠙⢻⡙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠈⠉⠓⣶⢤⡇
⠀⣿⠶⣛⣭⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠈⢻⣆⠀⠹⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠘⣧⢠⠏⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⡟⢦⡀
⠀⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠙⣷⡀⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⣿⣿⡀⠙⢿⡆⠠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⢀⡴⠋⢸⡇
⠀⡇⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠈⢳⣿⣿⣿⣿⣿⣿⡟⠃⣾⣿⣿⣿⣿⣿⣿⡇⢘⣏⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡴⠞⠋⢀⠐⢸⡇
⠀⡇⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⡿⠟⢃⠀⢠⣿⣿⣿⣿⣿⣿⣿⡇⠘⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⢀⠀⠄⢸⡇
⠀⡇⠈⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠉⠛⠛⠛⠛⠛⠛⠓⠖⠲⠛⠋⠁⠐⠈⡀⠄⠈⠙⠻⢿⣿⣿⣿⣿⣧⡄⢹⡇⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠠⠈⢸⡇
⠀⡇⠀⠌⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⡐⠀⠄⠠⠐⢀⠐⠠⠀⠂⠄⠂⢁⠈⠄⠠⠐⠈⡀⠄⠂⠙⢿⣿⣿⣿⠇⢼⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣎⡀⠐⢸⡇
⠀⡇⠂⠀⠺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⢀⠠⠈⡀⢂⠐⡀⢂⠀⡁⠐⡀⠌⡀⢈⠀⢂⠁⡐⠀⡐⠀⠄⡀⠙⠿⣿⣦⠈⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡄⢸⡇
⠀⡇⠠⠁⠄⢻⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠄⠠⠀⠔⠠⠀⠄⠠⠀⡐⠠⠁⠠⠀⠄⠠⠈⠠⠀⠄⠐⠠⠈⠄⠠⠀⠄⠈⠙⠛⢉⡿⣻⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⢳⣸⡇
⠀⠓⠒⠒⠒⠚⠻⣿⣿⣿⣿⣿⣿⡿⠓⠒⠒⠒⠒⠒⠒⠒⠒⠒⠓⠒⠒⠒⠒⠒⠚⠒⠒⠓⠒⠚⠒⠒⠒⠒⠒⠒⠒⠓⠒⠒⠚⠓⠛⠒⠒⠚⠒⠓⠚⠚⠓⠛⠛⠛⠛⠛⠛⠚⠒⠃
 _____                 _ _                   _____                                         _
|  _  |               | | |                 /  __ \                                       (_)
| | | |_   _  __ _  __| | |_ _ __ ___  ___  | /  \/ ___  _ __ ___  _ __  _ __ ___  ___ ___ _  ___  _ __
| | | | | | |/ _` |/ _` | __| '__/ _ \/ _ \ | |    / _ \| '_ ` _ \| '_ \| '__/ _ \/ __/ __| |/ _ \| '_ \
\ \/' / |_| | (_| | (_| | |_| | |  __/  __/ | \__/\ (_) | | | | | | |_) | | |  __/\__ \__ \ | (_) | | | |
 \_/\_\\__,_|\__,_|\__,_|\__|_|  \___|\___|  \____/\___/|_| |_| |_| .__/|_|  \___||___/___/_|\___/|_| |_|
                                                                  |_|
)";
}

double compress(const string& outputPath, int &threshold, const double targetRatio, Image &image,
    chrono::steady_clock::time_point *start, chrono::steady_clock::time_point *end) {
    double ratio;
    if (targetRatio > 0) {
        int left = 1, right = 255;

        const Image original(image);
        Quadtree::setThreshold(threshold);

        // Binary search for the threshold
        *start = chrono::steady_clock::now();

        // First iteration
        image = original;
        Quadtree::Compress();
        image.save(outputPath);
        ratio = static_cast<double>(Image::sizeAfter) / static_cast<double>(Image::sizeBefore);
        cout << "/";

        while (ratio > targetRatio) { // Get the initial range
            right += 100;
            left = threshold;
            Quadtree::setThreshold(threshold = right);

            image = original;
            Quadtree::Compress();
            image.save(outputPath);

            ratio = static_cast<double>(Image::sizeAfter) / static_cast<double>(Image::sizeBefore);
            cout << "/";
        }

        while (left != right) { // Binary search
            threshold = (left + right) / 2;
            Quadtree::setThreshold(threshold);

            image = original;
            Quadtree::Compress();
            image.save(outputPath);

            ratio = static_cast<double>(Image::sizeAfter) / static_cast<double>(Image::sizeBefore);
            cout << "/";

            if (ratio > targetRatio) {
                left = left == threshold ? right : threshold;
            } else {
                right = threshold;
            }
        }
        *end = chrono::steady_clock::now();
        cout << endl << "Final threshold: " << threshold << endl;
    } else {
        *start = chrono::steady_clock::now();
        Quadtree::Compress();
        *end = chrono::steady_clock::now();
        image.save(outputPath);
        ratio = static_cast<double>(Image::sizeAfter) / static_cast<double>(Image::sizeBefore);
    }
    return ratio;
}

void openOut(const string& outputPath) {
    #ifdef _WIN32
    // Open the output image using the default image viewer
    char fullPath[MAX_PATH];
    if (GetFullPathNameA(outputPath.c_str(), MAX_PATH, fullPath, nullptr) == 0) {
        cerr << "Failed to get the full path of the output file." << endl;
    }
    ShellExecute(nullptr, "Open", fullPath, nullptr, nullptr, SW_SHOW);
    #endif
}

int main() {
    miku(); // Splash Art :3

    string inputPath, outputPath;
    int method, threshold, minBlockSize;
    double targetRatio;

    cout << "Enter the path to your image:" << endl;
    cin >> inputPath;

    Image image = Image(inputPath);
    if (!image.isLoaded()) {
        cerr << "Failed to load image. Please check the file path." << endl;
        return 1;
    }
    Quadtree::setImage(image);

    cout << "1. Variance\n2. Mean Abosolute Deviation\n3. Max Pixel Difference\n4. Entropy" << endl;
    cout << "Enter the method of compression (1 to 4):" << endl;
    cin >> method;
    if (method < 1 || method > 4) {
        cerr << "Invalid method. Please enter a number between 1 and 4." << endl;
        return 1;
    }
    Quadtree::setMethod(method);

    cout << "Enter the threshold value (e.g., 63):" << endl;
    cin >> threshold;
    if (threshold < 0) {
        cerr << "Invalid threshold. Please enter a non-negative number." << endl;
        return 1;
    }
    Quadtree::setThreshold(threshold);

    cout << "Enter the minimum block size (e.g., 15):" << endl;
    cin >> minBlockSize;
    if (minBlockSize < 1) {
        cerr << "Invalid block size. Please enter a no.,...-negative number." << endl;
        return 1;
    }
    Quadtree::setMinBlockSize(minBlockSize);

    cout << "Enter the target compression ratio (e.g., 0.5). Enter 0 to ignore:" << endl;
    cin >> targetRatio;
    if (targetRatio < 0) {
        cerr << "Invalid ratio. Please enter a non-negative number." << endl;
        return 1;
    }

    cout << "Enter the output path for the processed image:" << endl;
    cin >> outputPath;

    cout << "Processing image..." << endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    chrono::steady_clock::time_point end;

    const double ratio = compress(outputPath, threshold, targetRatio, image, &begin, &end);

    const auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << endl << "Processing completed in " << elapsedTime << " ms." << endl;

    cout << "Size before compression: " << Image::sizeBefore << " bytes" << endl;
    cout << "Size after compression: " <<  Image::sizeAfter << " bytes" << endl;
    cout << "Compression ratio: " << ratio * 100 << "%" << endl;

    cout << "Tree depth: " << Quadtree::maxDepth << endl;
    cout << "Number of nodes: " << Quadtree::nodes << endl;

    openOut(outputPath);

    cout << endl << "(≧∇≦)ﾉ Thank you for using this program!" << endl;
    return 0;
}