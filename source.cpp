#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    string getName() const {
        return taskName;
    }
    string getDescription() const {
        return taskDescription;
    }
    bool isComplete() const {
        return completed;
    }

    void setName(const string& taskName) {
        this->taskName = taskName;
    }
    void setDescription(const string& taskDescription) {
        this->taskDescription = taskDescription;
    }
    void markCompleted(bool comPen) {
        completed = comPen;
    }

    void displayTask() const;
};

class ToDoList {
private:
    char userInput = '0';
    int taskNumber = 0;
    vector<Task> tasks;
public:
    void displayMenu();
    void addTask();
    void deleteTask();
    void editTask();
    void markTaskCompleted();
    void markTaskPending();
    void displayTasks();
    void runProgram();
    void saveTasksToFile();
    void loadTasksFromFile();
};

int main() {
    enableANSIColors();

    clrscr();
    cout << endl;

    setColor(9); // Light Blue
    typewriter("Welcome To The To-Do CLI App...", 45);

    setColor(7); // Reset to default (White)
    typewriter("Starting...", 35);

    pause(450);

    ToDoList toDoList;
    toDoList.runProgram();

    cin.get();
    return 0;
}

void Task::displayTask() const {
    if (completed) {
        setColor(10);
    }
    else {
        setColor(12);
    }
    cout << taskName << " ("
        << (completed ? "completed" : "pending")
        << ")" << endl
        << "Description: " << taskDescription << endl;

    setColor(7);
}

void ToDoList::displayMenu() {

    while (true) {
        clrscr();
        cout << "================== Home ==================" << endl;

        cout << endl;
        cout << "1) Add Task." << endl;
        cout << "2) Edit Task." << endl;
        cout << "3) Delete Task." << endl;
        cout << "4) Mark Task as Completed." << endl;
        cout << "5) Mark Task as Pending." << endl;
        cout << "6) Display all Tasks." << endl;
        cout << "7) Exit." << endl;
        setColor(15);
        cout << "Enter your Choice (1-7) :: ";
        cin >> userInput;
        setColor(7);

        switch (userInput) {
        case '1': addTask(); break;
        case '2': editTask(); break;
        case '3': deleteTask(); break;
        case '4': markTaskCompleted(); break;
        case '5': markTaskPending(); break;
        case '6': displayTasks(); break;
        case '7':
            cout << "Exiting Program..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid Selection... Select option (1-6)... ";
            continue;
        }
    }
}

void ToDoList::addTask() {
    clrscr();
    cout << "================ Add Task ================" << endl << endl;

    string name, description;

    setColor(11); // Light Aqua
    cout << "\033[1mEnter the Task Name -> \033[0m";
    cin >> ws; getline(cin, name);

    setColor(3); // Aqua
    cout << endl << "\033[1mEnter the Description \n:> \033[0m";
    cin >> ws; getline(cin, description);
    setColor(7); // default
    
    tasks.emplace_back(name, description);
    saveTasksToFile();
    setColor(2);
    cout << endl << "Task Added Successfully...";
    setColor(7);
    cout << "\nPress Enter to continue...";
    cin.get();
}

void ToDoList::deleteTask() {
    clrscr(); 
    cout << "=============== Delete Task ==============" << endl << endl;

    if (tasks.empty()) {
        setColor(4);
        cout << "No Task to delete... \nPress Enter to continue...";
        setColor(7);
        cin.ignore(); cin.get();
        return;
    }

    for (int i = 0; i < tasks.size(); ++i) {
        cout << "Task " << i + 1 << " " << tasks[i].getName() << endl;
    }

    while (true) {
        setColor(15);
        cout << "Enter the Task number you want to Delete \n(1 - " << tasks.size() << ") :: ";
        cin >> taskNumber;
        setColor(7);

        if (taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks.erase(tasks.begin() + taskNumber - 1);
            saveTasksToFile();
            setColor(2);
            cout << "Task Deleted Successfully...";
            setColor(7);
            cout << "\nPress Enter to continue...";
            cin.ignore(); cin.get();
            break;
        }
        else {
            setColor(4);
            cout << "Invalid Input. Try again..." << endl;
            setColor(7);
        }
    }
}

void ToDoList::editTask() {
    string name, description;
    clrscr(); 
    cout << "=============== Edit Task ================" << endl << endl;

    if (tasks.empty()) {
        setColor(4);
        cout << "No Task to Edit... \nPress Enter to continue...";
        setColor(7);
        cin.ignore(); cin.get();
        return;
    }

    for (int i = 0; i < tasks.size(); ++i) {
        cout << "Task " << i + 1 << " " << tasks[i].getName() << endl;
    }

    while (true) {
        setColor(15);
        cout << "Enter the Task number you want to Edit \n(1 - " << tasks.size() << ") :: ";
        cin >> taskNumber;
        setColor(7);

        if (taskNumber >= 1 && taskNumber <= tasks.size()) {
            Task& task = tasks[taskNumber - 1];
            setColor(13);
            cout << "Enter New Task Name :: ";
            cin >> ws; getline(cin, name);
            setColor(5);
            cout << "Enter New Task Description \n:> ";
            cin >> ws; getline(cin, description);
            setColor(7);

            task.setName(name);
            task.setDescription(description);
            saveTasksToFile();

            setColor(2);
            cout << "Task updated successfully!";
            setColor(7);
            cout << "\nPress Enter to continue...";
            cin.ignore(); cin.get();
            break;
        }
        else {
            setColor(4);
            cout << "Invalid Input. Try again..." << endl;
            setColor(7);
        }
    }
}

void ToDoList::markTaskCompleted() {
    clrscr(); 
    cout << "============== Marking Task ==============" << endl << endl;

    if (tasks.empty()) {
        setColor(4);
        cout << "No Task to To Mark as Completed... \nPress Enter to continue...";
        setColor(7);
        cin.ignore(); cin.get();
        return;
    }

    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].isComplete()) {
            setColor(10); // Green
        } else {
            setColor(12); // Red
        }
        cout << "Task " << i + 1 << " " << tasks[i].getName()  << endl;
    }
    setColor(7);

    while (true) {
        setColor(15);
        cout << "Enter the Task number you want to \nMark as Completed (1 - " << tasks.size() << ") :: ";
        cin >> taskNumber;
        setColor(7);

        if (taskNumber >= 1 && taskNumber <= tasks.size()) {

            Task& selectedTask = tasks[taskNumber - 1];

            if (selectedTask.isComplete()) {
                setColor(4);
                cout << "Task already completed... \nPlease select a different task.\n";
                setColor(7);
                continue; // go back to start of loop
            }
        }
        
        if (taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks[taskNumber - 1].markCompleted(true);
            saveTasksToFile();
            setColor(2);
            cout << "Task Marked as Completed successfully!";
            setColor(7);
            cout << "\nPress Enter to continue...";
            cin.ignore(); cin.get();
            break;
        }
        else {
            setColor(4);
            cout << "Invalid Selection. Try again..." << endl;
            setColor(7);
        }
    }
}

void ToDoList::markTaskPending() {
    clrscr(); 
    cout << "============== Marking Task ==============" << endl << endl;

    if (tasks.empty()) {
        setColor(4);
        cout << "No Task to To Mark as Completed... \nPress Enter to continue...";
        setColor(7);
        cin.ignore(); cin.get();
        return;
    }

    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].isComplete()) {
            setColor(10); // Green
        } else {
            setColor(12); // Red
        }
        cout << "Task " << i + 1 << " " << tasks[i].getName()  << endl;
    }
    setColor(7);

    while (true) {
        setColor(15);
        cout << "Enter the Task number you want to \nMark as Pending (1 - " << tasks.size() << ") :: ";
        cin >> taskNumber;
        setColor(7);

        if (taskNumber >= 1 && taskNumber <= tasks.size()) {

            Task& selectedTask = tasks[taskNumber - 1];

            if (!selectedTask.isComplete()) {
                setColor(4);
                cout << "Task already Pending... \nPlease select a different task.\n";
                setColor(7);
                continue; // go back to start of loop
            }
        }
        
        if (taskNumber >= 1 && taskNumber <= tasks.size()) {
            tasks[taskNumber - 1].markCompleted(false);
            saveTasksToFile();
            setColor(2);
            cout << "Task Marked as Pending successfully!";
            setColor(7);
            cout << "\nPress Enter to continue...";
            cin.ignore(); cin.get();
            break;
        }
        else {
            setColor(4);
            cout << "Invalid Selection. Try again..." << endl;
            setColor(7);
        }
    }
}

void ToDoList::displayTasks() {
    clrscr(); 
    cout << "============ Displaying Tasks ============" << endl << endl;

    if (tasks.empty()) {
        setColor(4);
        cout << "No Task to Display... \nPress Enter to continue...";
        setColor(7);
        cin.ignore(); cin.get();
        return;
    }

    for (int i = 0; i < tasks.size(); ++i) {
        cout << "Task " << i + 1 << ":\n";
        tasks[i].displayTask();
        cout << "------------------------------------------\n";
        cout << endl;
    }

    setColor(2);
    cout << "All Tasks Displayed Successfully"; 
    setColor(7);
    cout << "\nPress Enter to continue...";
    cin.ignore(); cin.get();
}

void ToDoList::runProgram() {
    loadTasksFromFile();
    displayMenu();
}

void ToDoList::saveTasksToFile() {
    fstream taskFile("userTask.txt", ios::out | ios::trunc);
    if (!taskFile.is_open()) {
        cerr << "Error: Could not open the file for writing..." << endl;
        exit(1);
    }
    for (const Task& task : tasks) {
        taskFile << task.getName() << "|"
            << task.getDescription() << "|"
            << task.isComplete() << endl;
    }
    taskFile.close();
}

void ToDoList::loadTasksFromFile() {
    ifstream taskFile("userTask.txt");
    if (!taskFile.is_open()) {
        //cerr << "Error: Could not open the file for reading..." << endl;
        return;
    }

    tasks.clear();
    string line;

    while (getline(taskFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            cerr << "Warning: Malformed line skipped." << endl;
            continue;
        }

        string name = line.substr(0, pos1);
        string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string completedStr = line.substr(pos2 + 1);

        Task task(name, description);
        if (completedStr == "1") task.markCompleted(true);

        tasks.push_back(task);
    }

    taskFile.close();
}
