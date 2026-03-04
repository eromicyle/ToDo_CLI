#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "conslmanip.h"

using namespace std;

class Task {
private:
    string taskName, taskDescription;
    bool completed;
public:
    Task(const string& taskName, const string& taskDescription)
        : taskName(taskName)
        , taskDescription(taskDescription)
        , completed(false)
    {
    }

    string getName()        const { return taskName; }
    string getDescription() const { return taskDescription; }
    bool   isComplete()     const { return completed; }

    void setName(const string& name)        { taskName = name; }
    void setDescription(const string& desc) { taskDescription = desc; }
    void markCompleted(bool value)          { completed = value; }

    void displayTask() const;
};

class ToDoList {
private:
    vector<Task> tasks;

    int readTaskNumber(int min, int max) const;
    void markTask(bool markAsCompleted);
    void printTaskList(bool showStatus = false) const;

public:
    void displayMenu();
    void addTask();
    void deleteTask();
    void editTask();
    void toggleTaskStatus();
    void displayTasks();
    void runProgram();
    void saveTasksToFile();
    void loadTasksFromFile();
};

int main() {
    enableANSIColors();
    clrscr();
    cout << endl;

    setColor(9);
    typewriter("Welcome To The To-Do CLI App...", 45);
    setColor(7);
    typewriter("Starting...", 35);
    pause(450);

    ToDoList toDoList;
    toDoList.runProgram();

    cin.get();
    return 0;
}

void Task::displayTask() const {
    setColor(completed ? 10 : 12);
    cout << taskName
         << " (" << (completed ? "completed" : "pending") << ")\n"
         << "Description: " << taskDescription << "\n";
    setColor(7);
}

int ToDoList::readTaskNumber(int min, int max) const {
    int number;
    while (true) {
        setColor(15);
        cout << "Enter task number (" << min << " - " << max << ") :: ";
        setColor(7);

        if (cin >> number) {
            if (number >= min && number <= max) return number;
            setColor(4);
            cout << "Out of range. Try again...\n";
            setColor(7);
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor(4);
            cout << "Invalid input. Enter a number.\n";
            setColor(7);
        }
    }
}

void ToDoList::printTaskList(bool showStatus) const {
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (showStatus) setColor(tasks[i].isComplete() ? 10 : 12);
        cout << "Task " << i + 1 << ": " << tasks[i].getName();
        if (showStatus)
            cout << " [" << (tasks[i].isComplete() ? "completed" : "pending") << "]";
        cout << "\n";
    }
    setColor(7);
}

void ToDoList::displayMenu() {
    while (true) {
        clrscr();

        size_t total = tasks.size();
        size_t completed = 0;
        for (const Task& t : tasks) if (t.isComplete()) ++completed;
        size_t pending = total - completed;

        setColor(15);
        cout << "================== Home ==================\n";
        setColor(7);
        cout << " Tasks: " << total
             << "  |  ";
        setColor(10); cout << "Completed: " << completed;
        setColor(7);  cout << "  |  ";
        setColor(12); cout << "Pending: " << pending;
        setColor(7);  cout << "\n";
        setColor(15);
        cout << "==========================================\n\n";
        setColor(7);

        cout << "1) Add Task\n";
        cout << "2) Edit Task\n";
        cout << "3) Delete Task\n";
        cout << "4) Toggle Task Status (Completed / Pending)\n";
        cout << "5) Display All Tasks\n";
        cout << "0) Exit\n\n";

        setColor(15);
        cout << "Enter your Choice (1-6) :: ";
        char userInput;
        cin >> userInput;
        setColor(7);

        switch (userInput) {
        case '1': addTask();          break;
        case '2': editTask();         break;
        case '3': deleteTask();       break;
        case '4': toggleTaskStatus(); break;
        case '5': displayTasks();     break;
        case '0':
            cout << "\nExiting Program...\n";
            return;
        default:
            setColor(4);
            cout << "Invalid selection. Choose between 1 and 6.\n";
            setColor(7);
            pause(900);
        }
    }
}

void ToDoList::addTask() {
    clrscr();
    cout << "================ Add Task ================\n\n";

    string name, description;

    setColor(11);
    cout << "\033[1mEnter the Task Name -> \033[0m";
    cin >> ws; getline(cin, name);

    setColor(3);
    cout << "\n\033[1mEnter the Description\n:> \033[0m";
    cin >> ws; getline(cin, description);
    setColor(7);

    tasks.emplace_back(name, description);
    saveTasksToFile();

    setColor(2);
    cout << "\nTask added successfully.";
    setColor(7);
    cout << "\nPress Enter to continue...";
    cin.get();
}

void ToDoList::deleteTask() {
    clrscr();
    cout << "=============== Delete Task ==============\n\n";

    if (tasks.empty()) {
        setColor(4); cout << "No tasks to delete.\n"; setColor(7);
        cout << "Press Enter to continue...";
        cin >> ws; cin.get();
        return;
    }

    printTaskList(true);
    cout << "\n";

    int taskNumber = readTaskNumber(1, static_cast<int>(tasks.size()));
    tasks.erase(tasks.begin() + taskNumber - 1);
    saveTasksToFile();

    setColor(2); cout << "Task deleted successfully."; setColor(7);
    cout << "\nPress Enter to continue...";
    cin >> ws; cin.get();
}

void ToDoList::editTask() {
    clrscr();
    cout << "=============== Edit Task ================\n\n";

    if (tasks.empty()) {
        setColor(4); cout << "No tasks to edit.\n"; setColor(7);
        cout << "Press Enter to continue...";
        cin >> ws; cin.get();
        return;
    }

    printTaskList(true);
    cout << "\n";

    int taskNumber = readTaskNumber(1, static_cast<int>(tasks.size()));
    Task& task = tasks[taskNumber - 1];

    string name, description;
    setColor(13);
    cout << "Enter new Task Name :: ";
    cin >> ws; getline(cin, name);

    setColor(5);
    cout << "Enter new Task Description\n:> ";
    cin >> ws; getline(cin, description);
    setColor(7);

    task.setName(name);
    task.setDescription(description);
    saveTasksToFile();

    setColor(2); cout << "Task updated successfully."; setColor(7);
    cout << "\nPress Enter to continue...";
    cin >> ws; cin.get();
}

void ToDoList::toggleTaskStatus() {
    clrscr();
    cout << "============= Toggle Task Status =========\n\n";

    if (tasks.empty()) {
        setColor(4); cout << "No tasks available.\n"; setColor(7);
        cout << "Press Enter to continue...";
        cin >> ws; cin.get();
        return;
    }

    printTaskList(true);
    cout << "\n";

    int taskNumber = readTaskNumber(1, static_cast<int>(tasks.size()));
    Task& task = tasks[taskNumber - 1];

    bool nowCompleted = !task.isComplete();
    task.markCompleted(nowCompleted);
    saveTasksToFile();

    setColor(2);
    cout << "Task marked as " << (nowCompleted ? "completed" : "pending") << ".\n";
    setColor(7);
    cout << "Press Enter to continue...";
    cin >> ws; cin.get();
}

void ToDoList::displayTasks() {
    clrscr();
    cout << "============ Displaying Tasks ============\n\n";

    if (tasks.empty()) {
        setColor(4); cout << "No tasks to display.\n"; setColor(7);
        cout << "Press Enter to continue...";
        cin >> ws; cin.get();
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << "Task " << i + 1 << ":\n";
        tasks[i].displayTask();
        cout << "------------------------------------------\n\n";
    }

    setColor(2); cout << "All tasks displayed."; setColor(7);
    cout << "\nPress Enter to continue...";
    cin >> ws; cin.get();
}

static const char DELIM = '\x01';

void ToDoList::saveTasksToFile() {
    fstream taskFile("userTask.txt", ios::out | ios::trunc);
    if (!taskFile.is_open()) {
        setColor(4);
        cerr << "\nError: Could not open file for writing. Changes not saved.\n";
        setColor(7);
        return;
    }
    for (const Task& task : tasks) {
        taskFile << task.getName()        << DELIM
                 << task.getDescription() << DELIM
                 << task.isComplete()     << "\n";
    }
    taskFile.close();
}

void ToDoList::loadTasksFromFile() {
    ifstream taskFile("userTask.txt");
    if (!taskFile.is_open()) return;

    tasks.clear();
    string line;

    while (getline(taskFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find(DELIM);
        size_t pos2 = line.find(DELIM, pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            cerr << "Warning: malformed line skipped.\n";
            continue;
        }

        string name        = line.substr(0, pos1);
        string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string completedStr = line.substr(pos2 + 1);

        Task task(name, description);
        if (completedStr == "1") task.markCompleted(true);
        tasks.push_back(task);
    }

    taskFile.close();
}

void ToDoList::runProgram() {
    loadTasksFromFile();
    displayMenu();
}