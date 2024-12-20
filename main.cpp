#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Task {
    string title;
    string dueDate;
    int priority;
    bool completed;
};
vector<Task> tasks;

// Function prototypes
void displayMenu();
void addTask(vector<Task>& tasks);
void editTask(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void saveTasksToFile(const vector<Task>& tasks);
void loadTasksFromFile(vector<Task>& tasks);
void filterAndSortTasks(vector<Task>& tasks);

int main() {
    loadTasksFromFile(tasks);

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore leftover newline

        switch (choice) {
            case 1: addTask(tasks);
            break;
            case 2: editTask(tasks);
            break;
            case 3: deleteTask(tasks);
            break;
            case 4: markTaskCompleted(tasks);
            break;
            case 5: viewTasks(tasks);
            break;
            case 6: filterAndSortTasks(tasks);
            break;
            case 7: saveTasksToFile(tasks);
            break;
            case 8: cout << "Exiting program...\n";
            break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}

void displayMenu() {
    cout << "\n--- To-Do List Manager ---\n";
    cout << "1. Add Task\n";
    cout << "2. Edit Task\n";
    cout << "3. Delete Task\n";
    cout << "4. Mark Task as Completed\n";
    cout << "5. View Tasks\n";
    cout << "6. Filter and Sort Tasks\n";
    cout << "7. Save Tasks to File\n";
    cout << "8. Exit\n";
    if (tasks.capacity()==1) {
        cout << endl <<"You have "<< tasks.capacity() << " task" << endl;
    }
    else
        cout << endl <<"You have "<< tasks.capacity() << " tasks" << endl;
}

void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task title: ";
    getline(cin, newTask.title);
    cout << "Enter due date (YYYY-MM-DD): ";
    getline(cin, newTask.dueDate);
    cout << "Enter priority (1-5): ";
    cin >> newTask.priority;
    cin.ignore();
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully."<<endl;
}

void editTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to edit (starting from 1): ";
    cin >> index;
    cin.ignore();

    if (index >= 1 && index <= tasks.size()) {
        index -= 1;
        cout << "Editing Task: " << tasks[index].title << "\n";
        cout << "Enter new title: ";
        getline(cin, tasks[index].title);
        cout << "Enter new due date (YYYY-MM-DD): ";
        getline(cin, tasks[index].dueDate);
        cout << "Enter new priority (1-5): ";
        cin >> tasks[index].priority;
        cin.ignore();
        cout << "Task updated successfully.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}


void deleteTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to delete (starting from 1): ";
    cin >> index;
    cin.ignore();

    // Adjust 1-based index to 0-based for internal use
    if (index >= 1 && index <= tasks.size()) {
        index -= 1; // Convert to 0-based index
        tasks.erase(tasks.begin() + index);
        cout << "Task deleted successfully.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}


void markTaskCompleted(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to mark as completed (starting from 1): ";
    cin >> index;
    cin.ignore();


    if (index >= 1 && index <= tasks.size()) {
        index -= 1;
        tasks[index].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

void viewTasks(const vector<Task>& tasks) {
    cout << "\n--- Task List ---"<<endl;
    int completedCount = 0;
    for (int i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        cout << i +1 << ". " << task.title << " | Due: " << task.dueDate
             << " | Priority: " << task.priority
             << " | Status: " << (task.completed ? "Completed" : "Pending") << ""<<endl;
        if (task.completed) ++completedCount;
    }
    cout << "Completion Percentage: " << (tasks.empty() ? 0 : (completedCount * 100) / tasks.size()) << "%"<<endl;
}

void saveTasksToFile(const vector<Task>& tasks) {
    ofstream outFile("tasks.txt");
    for (const auto& task : tasks) {
        outFile << task.title << "\n" << task.dueDate << "\n"
                << task.priority << "\n" << task.completed << "\n";
    }
    outFile.close();
    cout << "Tasks saved successfully.\n";
}

void loadTasksFromFile(vector<Task>& tasks) {
    ifstream inFile("tasks.txt");
    if (!inFile) return;

    Task task;
    while (getline(inFile, task.title)) {
        getline(inFile, task.dueDate);
        inFile >> task.priority >> task.completed;
        inFile.ignore();
        tasks.push_back(task);
    }
    inFile.close();
}

void filterAndSortTasks(vector<Task>& tasks) {
    int choice;
    cout << "1. Filter by status (1: Completed, 0: Pending)\n";
    cout << "2. Sort by priority\n";
    cout << "3. Sort by due date\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        bool status;
        cout << "Enter status (Write 1 to sort by Completed, Write 0 to sort by Pending): ";
        cin >> status;
        cin.ignore();
        for (const auto& task : tasks) {
            if (task.completed == status) {
                cout << task.title << " | Due: " << task.dueDate
                     << " | Priority: " << task.priority << "\n";
            }
        }
    } else if (choice == 2) {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority < b.priority;
        });
        cout << "Tasks sorted by priority.\n";
    } else if (choice == 3) {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.dueDate < b.dueDate;
        });
        cout << "Tasks sorted by due date.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}
