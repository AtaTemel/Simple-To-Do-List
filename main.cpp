#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <regex>
#include <sstream>

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

        if (!(cin >> choice)) { // Validate input
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue; // Restart the loop
        }

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
            default: cout << "Invalid choice. Please select a valid option.\n";
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

    size_t taskCount = tasks.size();
    cout << endl << "You have " << taskCount
         << (taskCount == 1 ? " task" : " tasks") << endl;
}

#include <regex> // Include regex for date validation

#include <regex>
#include <sstream>

bool isValidDate(const string& date) {
    // Regex to check basic format YYYY-MM-DD
    regex datePattern(R"(\d{4}-(\d{2})-(\d{2}))");
    smatch matches;

    if (!regex_match(date, matches, datePattern)) {
        return false;
    }

    // Extract year, month, and day
    int year, month, day;
    char dash1, dash2;
    stringstream ss(date);
    ss >> year >> dash1 >> month >> dash2 >> day;

    // Validate the month and day
    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    // Handle days in specific months
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false; // April, June, September, November have 30 days
    }

    // Handle February (leap years considered)
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeapYear)) {
            return false;
        }
    }

    return true;
}

void addTask(vector<Task>& tasks) {
    Task newTask;

    cout << "Enter task title: ";
    getline(cin, newTask.title);

    // Check for duplicate titles
    auto it = find_if(tasks.begin(), tasks.end(), [&newTask](const Task& task) {
        return task.title == newTask.title;
    });

    if (it != tasks.end()) {
        cout << "A task with this title already exists. Please use a different title.\n";
        return;
    }

    // Validate due date
    do {
        cout << "Enter due date (YYYY-MM-DD): ";
        getline(cin, newTask.dueDate);
        if (!isValidDate(newTask.dueDate)) {
            cout << "Invalid date. Ensure the format is YYYY-MM-DD, and the month/day are valid.\n";
        }
    } while (!isValidDate(newTask.dueDate));

    // Validate priority input
    do {
        cout << "Enter priority (1-100): ";
        cin >> newTask.priority;
        if (newTask.priority < 1 || newTask.priority > 100) {
            cout << "Invalid priority. Please enter a number between 1 and 100.\n";
        }
    } while (newTask.priority < 1 || newTask.priority > 100);

    cin.ignore(); // Ignore leftover newline
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully.\n";
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
