
# QR Code Reader

A desktop application built with **C++** and **OpenCV** that uses a **webcam** to scan and read QR codes. The application extracts and displays the content of QR codes using a simple **UI**, and stores both the image and its decoded content into a **JSON** file for future reference.

---

## 🔧 Features

- 📷 Real-time QR code detection using webcam
- 📄 Displays the decoded content in a user-friendly UI
- 💾 Automatically saves the captured image and data to a `.json` file
- 🖥️ Built with C++ and OpenCV

---

## 🛠️ Technologies Used

- **C++**
- **OpenCV**
- **zxing** (for decoding)
- **nlohmann/json** (for JSON handling)
- **Qt**

---

## 📁 Project Structure

```
/project-root
├── CMakeLists.txt
├── vcpkg.json
├── src/
│ ├── main.cpp
├── libs/
│ ├── FrameHandler/
│ │ ├── FrameHandler.h
│ │ ├── FrameHandler.cpp
│ │ └── CMakeLists.txt
│ ├── Scanner/
│ │ ├── Scanner.h
│ │ ├── Scanner.cpp
│ │ └── CMakeLists.txt
│ ├── UI/
│ │ ├── UI.h
│ │ ├── UI.cpp
│ │ └── CMakeLists.txt
│ ├── Archive/
│ │ ├── Archive.h
│ │ ├── Archive.cpp
│ │ └── CMakeLists.tx
```

---

## 🧑‍💻 Team Members

- **Sayed AmirReza Ghamilouei**
- **Mahdi Azarbad**
- **Alireza Jahani**
- **Seyed Mojtaba Tabatabei**
- **Mohadeseh Rajabion**
- **Kabiri**

---

## 🚀 Getting Started

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your-repo/qr-code-reader.git
   cd qr-code-reader
   ```

2. **Install Dependencies:**
   Make sure you have OpenCV, Qt and a C++ compiler installed.

3. **Build the project:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the application:**
   ```bash
   ./main
   ```

---

## 📌 Future Improvements

- We don't know yet

---

## 📄 License

This project is for academic and educational use only.
