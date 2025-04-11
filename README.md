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

- Windows :(

---

## 🚀 How to Run

1. **Clone the repo**
   ```bash
   git clone https://github.com/yourusername/quadtree-compression.git
   cd quadtree-compression
   ```

2. **Run the program**  
   Simply **double-click** the file:
   ```
   bin/Quad.exe
   ```

   > ⚠️ Make sure `stb_image.h` and `stb_image_write.h` are present in the working directory, as well as the required image file(s).

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
