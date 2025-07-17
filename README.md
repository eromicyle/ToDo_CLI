# 📝 ToDo_CLI - (C++)

**ToDo_CLI** is a **console-based To-Do list application** built in **C++**.
It allows you to create, edit, delete, and manage tasks right from your terminal.
The project uses **colored console output** and **typewriter effects** for a more interactive CLI experience, handled by the custom **`conslmanip.h`** header.

---

## 📂 Folder Structure

``` graphql
ToDo_CLI/
├── conslmanip.h       # Custom console utilities (colors, clear screen, etc.)
├── source.cpp          # Main application source code
├── userTask.txt        # Task storage (persistent data)
└── README.md           # Project documentation
```

---

## ⚙️ Features

* ✅ Add new tasks with description
* ✏️ Edit existing tasks
* ❌ Delete tasks
* ✅ Mark tasks as **completed** or **pending**
* 📋 View all tasks with color-coded status
* 💾 Persistent task storage in `userTask.txt`
* 🎨 ANSI color output (cross-platform)
* ⌨️ Typewriter text effect for UI animations

---

## 🚀 How to Run

### **Build**

#### Linux / MacOS:

```bash
g++ source.cpp -o ToDo_CLI
./ToDo_CLI
```

#### Windows (MinGW):

```bash
g++ source.cpp -o ToDo_CLI.exe
ToDo_CLI.exe
```

---

## 💾 Data Storage

All tasks are stored in a simple text file:

```
userTask.txt
```

Format:

```
taskName|taskDescription|completedFlag
```

Example:

```
Buy Groceries|Buy fruits and vegetables|0
Complete Project|Finish ToDo CLI App|1
```

---

## 🖥️ Console Output Preview

Example task display:

```
Task 1: 
Buy Groceries (pending)
Description: Buy fruits and vegetables
------------------------------------------

Task 2: 
Complete Project (completed)
Description: Finish ToDo CLI App
------------------------------------------
```

---

## 🗓️ Project Status

| Feature                         | Status |
| ------------------------------- | ------ |
| Basic Task Management           | ✅ Done |
| Persistent File Storage         | ✅ Done |
| Colored CLI & Typewriter Effect | ✅ Done |
| Cross-platform Support          | ✅ Done |

---

## 👨‍💻 Author

> **Eromicyle**

---

### ⭐ *If you find this project useful, consider starring the repository!*

---

### Badges
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-blue)
![Language](https://img.shields.io/badge/C%2B%2B-17-blueviolet)
![Status](https://img.shields.io/badge/status-Completed-success)

---