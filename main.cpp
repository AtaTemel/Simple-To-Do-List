#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Task {
    string title;
    string dueDate;
    int priority;
    bool completed;
};
vector<Task> tasks;

void displayMenu();
void addTask(vector<Task>& tasks);
void editTask(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void markTaskCompleted(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void saveTasksToFile(const vector<Task>& tasks);
void loadTasksFromFile(vector<Task>& tasks);
void filterAndSortTasks(vector<Task>& tasks);
bool isValidDate(const string& date);

int main() {
    loadTasksFromFile(tasks);

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: " << endl;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        cin.ignore();

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: deleteTask(tasks); break;
            case 3: editTask(tasks);break;
            case 4: viewTasks(tasks); break;
            case 5: markTaskCompleted(tasks);break;
            case 6: filterAndSortTasks(tasks); break;
            case 7: saveTasksToFile(tasks); break;
            case 8: cout << "Exiting program..." << endl; break;
            default: cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while (choice != 8);

    return 0;
}

void displayMenu() {
    cout << endl << "--- To-Do List Manager ---" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Delete Task"<< endl;
    cout << "3. Edit Task"<< endl;
    cout << "4. View Tasks" << endl;
    cout << "5. Mark Task as Completed"<< endl;
    cout << "6. Filter and Sort Tasks" << endl;
    cout << "7. Save Tasks to File" << endl;
    cout << "8. Exit" << endl;
    cout << "You have " << tasks.size() << (tasks.size() == 1 ? " task" : " tasks") << endl;
}

bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (month < 1 || month > 12 || day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day > 28 && !isLeap)) {
            return false;
        }
    }
    return true;
}

void addTask(vector<Task>& tasks) {
    Task newTask;

    cout << "Enter task title: " << endl;
    getline(cin, newTask.title);

    for (const auto& task : tasks) {
        if (task.title == newTask.title) {
            cout << "A task with this title already exists." << endl;
            return;
        }
    }

    do {
        cout << "Enter due date (YYYY-MM-DD): " << endl;
        getline(cin, newTask.dueDate);
        if (!isValidDate(newTask.dueDate)) {
            cout << "Invalid date. Ensure the format is YYYY-MM-DD." << endl;
        }
    } while (!isValidDate(newTask.dueDate));

    cout << "Enter priority (1-100): " << endl;
    while (!(cin >> newTask.priority) || newTask.priority < 1 || newTask.priority > 100) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid priority. Please enter a number between 1 and 100: " << endl;
    }
    cin.ignore();

    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully." << endl;
}

void editTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to edit: " << endl;
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size()) {
        Task& task = tasks[index - 1];
        cout << "Editing Task: " << task.title << endl;
        cout << "Enter new title: " << endl; getline(cin, task.title);
        do {
            cout << "Enter new due date (YYYY-MM-DD): " << endl; getline(cin, task.dueDate);
        } while (!isValidDate(task.dueDate));
        cout << "Enter new priority (1-100): " << endl;
        while (!(cin >> task.priority) || task.priority < 1 || task.priority > 100) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid priority. Try again: " << endl;
        }
        cin.ignore();
        cout << "Task updated successfully." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void deleteTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to delete: " << endl;
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task deleted successfully." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void markTaskCompleted(vector<Task>& tasks)//this function takes the number for the task from the user and marks it as completed.
{
    int index;
    cout << "Enter task number to mark as completed: " << endl;
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << "Task marked as completed." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void viewTasks(const vector<Task>& tasks) {
    cout << endl << "--- Task List ---" << endl;
    int completedCount = 0;
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        cout << i + 1 << ". " << task.title << " | Due: " << task.dueDate
             << " | Priority: " << task.priority
             << " | Status: " << (task.completed ? "Completed" : "Pending") << endl;
        if (task.completed) ++completedCount;
    }
    if (tasks.empty()) {
        cout << "Completion Percentage: 0%" << endl;
    } else {
        int completionPercentage = (completedCount * 100) / tasks.size();
        cout << "Completion Percentage: " << completionPercentage << "%" << endl;
    }

}

void saveTasksToFile(const vector<Task>& tasks) {
    ofstream outFile("tasks.txt");
    for (size_t i = 0; i < tasks.size(); ++i) {
        outFile << tasks[i].title << endl << tasks[i].dueDate << endl
                << tasks[i].priority << endl << tasks[i].completed << endl;
    }

    cout << "Tasks saved successfully." << endl;
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
}

void filterAndSortTasks(vector<Task>& tasks) {
    int choice;
    cout << "1. Filter by status (1: Completed, 0: Pending)" << endl;
    cout << "2. Sort by priority" << endl;
    cout << "3. Sort by due date" << endl;
    cout << "Enter your choice: " << endl;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        bool status;
        cout << "Enter status (1 for Completed, 0 for Pending): " << endl;
        cin >> status;
        cin.ignore();
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].completed == status) {
                cout << tasks[i].title << " | Due: " << tasks[i].dueDate
                     << " | Priority: " << tasks[i].priority << endl;
            }
        }

    } else if (choice == 2) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            for (size_t j = i + 1; j < tasks.size(); ++j) {
                if (tasks[i].priority > tasks[j].priority) {
                    swap(tasks[i], tasks[j]);
                }
            }
        }
        cout << "Tasks sorted by priority." << endl;
    } else if (choice == 3) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            for (size_t j = i + 1; j < tasks.size(); ++j) {
                if (tasks[i].dueDate > tasks[j].dueDate) {
                    swap(tasks[i], tasks[j]);
                }
            }
        }
        cout << "Tasks sorted by due date." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
}
