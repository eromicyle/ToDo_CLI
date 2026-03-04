# 📝 ToDo_CLI

**ToDo_CLI** is a **console-based To-Do list application** built in **C++**.
It allows you to create, edit, delete, and manage tasks right from your terminal.
The project uses **colored console output** and **typewriter effects** for a more interactive CLI experience, handled by the custom **`conslmanip.h`** header.

---

## ⚙️ Features

- **Add** tasks with a name and description
- **Edit** any existing task
- **Delete** tasks by number
- **Toggle** status between *completed* and *pending* in one step
- **Display** all tasks with color-coded status
- **Live summary** on the home screen — total / completed / pending at a glance
- **Persistent storage** — tasks are saved to `userTask.txt` automatically
- **Cross-platform color support** — ANSI on Linux/macOS & Windows 10+; WinAPI fallback for older Windows

---

## 📂 Project Structure

``` graphql
ToDo_CLI/
├── source.cpp        # Main application logic
├── conslmanip.h      # Cross-platform console utilities (colors, typewriter, clear)
├── CMakeLists.txt    # CMake build configuration
└── README.md         # Project documentation
```

---

## 🔧 Requirements

| Requirement  | Minimum Version |
| ------------ | --------------- |
| C++ Standard | C++17           |
| CMake        | 3.15            |
| Compiler     | GCC 8+, Clang7+ |

---

## 🚀 Building

### Using CMake (recommended)

```bash
# 1. Clone the repository
git clone https://github.com/eromicyle/ToDo_CLI.git
cd ToDo-CLI

# 2. Configure
cmake -B build

# 3. Build
cmake --build build

# 4. Run
./build/TodoCLI          # Linux / macOS
build\Debug\TodoCLI.exe  # Windows
```

### Manual (g++)

```bash
g++ -std=c++17 -O2 -o TodoCLI source.cpp
./TodoCLI
```

---

## 🖥️ Platform Notes

| Platform                                          | Color Support                             | Clear Screen                                 |
| ------------------------------------------------- | ----------------------------------------- | -------------------------------------------- |
| Linux / macOS                                     | ANSI escape codes                         | ANSI escape codes                            |
| Windows 10+ (cmd / PowerShell / Windows Terminal) | ANSI via Virtual Terminal Processing      | ANSI via VTP                                 |
| Windows (older cmd.exe, pre-Win10)                | WinAPI `SetConsoleTextAttribute` fallback | WinAPI `FillConsoleOutputCharacter` fallback |

---

## 💾 Data Storage

Tasks are saved to **`userTask.txt`** in the working directory using `\x01` (ASCII Unit Separator) as a field delimiter, so task names and descriptions can safely contain any printable character including `|`, commas, and quotes.

File format (one task per line):

```bash
name\x01description\x010_or_1
```

---

## 🖥️ Console Output Preview

``` txt
================== Home ==================
 Tasks: 4  |  Completed: 2  |  Pending: 2
==========================================

1) Add Task
2) Edit Task
3) Delete Task
4) Toggle Task Status (Completed / Pending)
5) Display All Tasks
6) Exit

Enter your Choice (1-6) ::
```

---

## 🗓️ Project Status

| Feature                         | Status  |
| ------------------------------- | ------- |
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
