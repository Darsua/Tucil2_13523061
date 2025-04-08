#include <iostream>
#include <windows.h>
#include <chrono>
#include <cmath>

#include "Image.h"
#include "Quadtree.h"

using namespace std;

void miku()
{
    SetConsoleOutputCP(CP_UTF8);
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
        cerr << "Invalid block size. Please enter a non-negative number." << endl;
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

    const chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    if (targetRatio > 0) {
        double ratio = 1;
        Quadtree::setThreshold(1);
        const Image original(image);
        while (targetRatio < ratio) {
            image = original;
            Quadtree::Compress();
            image.save(outputPath);
            ratio = static_cast<double>(Image::sizeAfter) / static_cast<double>(Image::sizeBefore);
            cout << "Current compression ratio: " << ratio * 100 << "% with threshold " << threshold << endl; // Debugging
            threshold += static_cast<int>(max(1.0, log((ratio - targetRatio) * 100)));
            Quadtree::setThreshold(threshold);
        }
    } else {
        Quadtree::Compress();
    }
    const chrono::steady_clock::time_point end = chrono::steady_clock::now();

    const auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << endl << "Processing completed in " << elapsedTime << " ms." << endl;

    if (targetRatio == 0) {image.save(outputPath);};

    targetRatio = static_cast<double>(Image::sizeAfter) / static_cast<double>(Image::sizeBefore);
    cout << "Size before compression: " << Image::sizeBefore << " bytes" << endl;
    cout << "Size after compression: " <<  Image::sizeAfter << " bytes" << endl;
    cout << "Compression ratio: " << targetRatio * 100 << "%" << endl;

    cout << "Tree depth: " << Quadtree::maxDepth << endl;
    cout << "Number of nodes: " << Quadtree::nodes << endl;

    // Open the output image using the default image viewer
    char fullPath[MAX_PATH];
    if (GetFullPathNameA(outputPath.c_str(), MAX_PATH, fullPath, nullptr) == 0) {
        cerr << "Failed to get the full path of the output file." << endl;
        return 1;
    }
    ShellExecute(nullptr, "open", fullPath, nullptr, nullptr, SW_SHOW);
    return 0;
}