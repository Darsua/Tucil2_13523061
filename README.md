# 🖼️ Quadtree-Based Image Compression

A C++ implementation of image compression using the **Quadtree** algorithm and the **Divide and Conquer** paradigm. This project analyzes and compresses images by partitioning them into smaller blocks, preserving detail in complex regions and simplifying uniform ones.

---

## 📦 Features

- Compress images using **quadtree decomposition**
- Choose from multiple error metrics:
  - Variance
  - Mean Absolute Deviation (MAD)
  - Max Pixel Difference (MPD)
  - Entropy
- Adjustable compression threshold and minimum block size
- Target compression ratio (with automatic threshold search)
- Visual splash screen (just for fun 😄)

---

## 🧠 How It Works

This program divides an image into 4 quadrants recursively until each block is "simple" enough based on the selected error metric and threshold. Each homogeneous block is normalized (i.e., replaced with the average color), while complex ones are split further.

The goal is to minimize image size while preserving as much visual fidelity as possible.

---

## 🛠️ Requirements

- C++17 compiler (e.g., g++)
- `stb_image` and `stb_image_write` libraries (included in the project)

---

## 🚀 How to Build and Run

1. **Clone the repo**
   ```bash
   git clone https://github.com/yourusername/quadtree-compression.git
   cd quadtree-compression
   ```

2. **Compile**
   You can use any C++ compiler. Example using g++:
   ```bash
   g++ -std=c++17 -O2 Main.cpp Quadtree.cpp Image.cpp -o compressor
   ```

3. **Run**
   ```bash
   ./compressor
   ```

---

## 📸 Input Format

- Supports standard image formats (e.g., PNG, JPG) via `stb_image`.
- Input path is entered interactively.
- Output is saved as PNG.

---

## 📊 Sample CLI Flow

```bash
Enter the path to your image:
> input.png

1. Variance
2. Mean Absolute Deviation
3. Max Pixel Difference
4. Entropy
Enter the method of compression (1 to 4):
> 1

Enter the threshold value (e.g., 63):
> 50

Enter the minimum block size (e.g., 15):
> 10

Enter the target compression ratio (e.g., 0.5). Enter 0 to ignore:
> 0.6

Enter the output path for the processed image:
> output.png
```

---

## 📈 Compression Metrics

- **Size before/after compression**
- **Compression ratio**
- **Tree depth**
- **Total number of nodes**

These are shown after the compression process is complete.

---


## 🙋‍♂️ Authors

- **Darrel Adinarya Sunanda** – [@Darsuas](https://github.com/Darsuas)

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 🌸 ASCII Splash Screen

Features a fun ASCII art of Miku to brighten your day before you compress things 😊
