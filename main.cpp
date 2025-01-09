#include <iostream>   // Library for input and output operations
#include <vector>     // Library for using the vector container
#include <fstream>    // Library for file operations
#include <string>     // Library for using strings

using namespace std;  // Using the standard namespace

// Struct to represent a Task with title, due date, priority, and completion status
struct Task {
    string title;      // Title of the task
    string dueDate;    // Due date of the task in YYYY-MM-DD format
    int priority;      // Priority level of the task (range: 1 to 100, where 1 is lowest and 100 is highest)
    bool completed;    // Status of the task (true if completed, false otherwise)
};

// Vector to store all tasks
vector<Task> tasks;

// Function prototypes
void displayMenu();                               // Displays the menu options to the user
void addTask(vector<Task>& tasks);                // Adds a new task to the list
void editTask(vector<Task>& tasks);               // Edits an existing task
void deleteTask(vector<Task>& tasks);             // Deletes a task from the list
void markTaskCompleted(vector<Task>& tasks);      // Marks a task as completed
void viewTasks(const vector<Task>& tasks);        // Displays all tasks to the user
void saveTasksToFile(const vector<Task>& tasks);  // Saves all tasks to a file
void loadTasksFromFile(vector<Task>& tasks);      // Loads tasks from a file
void filterAndSortTasks(vector<Task>& tasks);     // Filters and sorts tasks based on certain criteria
bool isValidDate(const string& date);             // Validates the format of a date string

int main() {
    // Precondition: The program should have access to the required file for loading tasks.
    loadTasksFromFile(tasks);  // Load tasks from file at the start of the program

    int choice;
    do {
        displayMenu();  // Display the menu options to the user
        cout << "Enter your choice: " << endl;

        if (!(cin >> choice)) {
            cin.clear();  // Clear the error flag on cin
            cin.ignore(10000, '\n');  // Ignore the invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;  // Prompt the user again
        }

        cin.ignore();  // Ignore the newline character after the number input

        // Process the user's choice
        switch (choice) {
            case 1: addTask(tasks); break;                     // Add a new task
            case 2: deleteTask(tasks); break;                  // Delete an existing task
            case 3: editTask(tasks); break;                    // Edit an existing task
            case 4: viewTasks(tasks); break;                      // View all tasks
            case 5: markTaskCompleted(tasks); break;           // Mark a task as completed
            case 6: filterAndSortTasks(tasks); break;          // Filter and sort tasks
            case 7: saveTasksToFile(tasks); break;                // Save tasks to file
            case 8: cout << "Exiting program..." << endl; break;  // Exit the program
            default: cout << "Invalid choice. Please select a valid option." << endl;  // Handle invalid choice
        }
    } while (choice != 8);

    // Post condition: All tasks will be saved back to the file before exiting the program.
    return 0;
}


// Function to display the menu options to the user
void displayMenu() {
    cout << endl << "--- To-Do List Manager ---" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Delete Task" << endl;
    cout << "3. Edit Task" << endl;
    cout << "4. View Tasks" << endl;
    cout << "5. Mark Task as Completed" << endl;
    cout << "6. Filter and Sort Tasks" << endl;
    cout << "7. Save Tasks to File" << endl;
    cout << "8. Exit" << endl;
    cout << "You have " << tasks.size() << (tasks.size() == 1 ? " task" : " tasks") << endl;

    // Precondition: None
    // Post condition: The menu options will be displayed to the user, showing the current number of tasks.
}

// Function to validate the format of a date string (expected format: YYYY-MM-DD)
bool isValidDate(const string& date) {

    // Precondition: The date string must be in the format YYYY-MM-DD.
    // Post condition: Returns true if the date is valid, otherwise returns false.

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


// Function to add a new task to the list
void addTask(vector<Task>& tasks) {
    Task newTask;

    // Precondition: The 'tasks' vector must be accessible and modifiable.
    // Post condition: A new task is added to the 'tasks' vector if it meets all validation criteria.

    // Prompt for task title
    cout << "Enter task title: " << endl;
    getline(cin, newTask.title);

    // Check for duplicate task titles
    for (const auto& task : tasks) {
        if (task.title == newTask.title) {
            cout << "A task with this title already exists." << endl;
            return;
        }
    }

    // Prompt for valid due date until a valid date is provided
    do {
        cout << "Enter due date (YYYY-MM-DD): " << endl;
        getline(cin, newTask.dueDate);
        if (!isValidDate(newTask.dueDate)) {
            cout << "Invalid date. Ensure the format is YYYY-MM-DD." << endl;
        }
    } while (!isValidDate(newTask.dueDate));

    // Prompt for valid priority (1-100) until a valid priority is provided
    cout << "Enter priority (1-100): " << endl;
    while (!(cin >> newTask.priority) || newTask.priority < 1 || newTask.priority > 100) {
        cin.clear();  // Clear the error flag on cin
        cin.ignore(10000, '\n');  // Ignore invalid input
        cout << "Invalid priority. Please enter a number between 1 and 100: " << endl;
    }
    cin.ignore();  // Ignore the newline character after the number input

    newTask.completed = false;  // Initialize task as not completed
    tasks.push_back(newTask);  // Add the new task to the vector
    cout << "Task added successfully." << endl;
}


// Function to edit an existing task in the list
void editTask(vector<Task>& tasks) {
    int index;

    // Precondition: The 'tasks' vector must be accessible and modifiable.
    // Post condition: The specified task is updated with new details if the index is valid.

    // Prompt for task number to edit
    cout << "Enter task number to edit: " << endl;
    cin >> index;
    cin.ignore();  // Ignore the newline character after the number input

    // Check if the index is valid
    if (index > 0 && index <= tasks.size()) {
        Task& task = tasks[index - 1];  // Access the task to be edited
        cout << "Editing Task: " << task.title << endl;

        // Prompt for new title
        cout << "Enter new title: " << endl;
        getline(cin, task.title);

        // Prompt for valid new due date until a valid date is provided
        do {
            cout << "Enter new due date (YYYY-MM-DD): " << endl;
            getline(cin, task.dueDate);
        } while (!isValidDate(task.dueDate));

        // Prompt for valid new priority (1-100) until a valid priority is provided
        cout << "Enter new priority (1-100): " << endl;
        while (!(cin >> task.priority) || task.priority < 1 || task.priority > 100) {
            cin.clear();  // Clear the error flag on cin
            cin.ignore(10000, '\n');  // Ignore invalid input
            cout << "Invalid priority. Try again: " << endl;
        }
        cin.ignore();  // Ignore the newline character after the number input

        cout << "Task updated successfully." << endl;
    } else {
        // Handle invalid task number
        cout << "Invalid task number." << endl;
    }
}

// Function to delete a task from the list
void deleteTask(vector<Task>& tasks) {
    int index;

    // Precondition: The 'tasks' vector must be accessible and modifiable.
    // Post condition: The specified task is removed from the 'tasks' vector if the index is valid.

    // Prompt for task number to delete
    cout << "Enter task number to delete: " << endl;
    cin >> index;
    cin.ignore();  // Ignore the newline character after the number input

    // Check if the index is valid
    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);  // Remove the task from the vector
        cout << "Task deleted successfully." << endl;
    } else {
        // Handle invalid task number
        cout << "Invalid task number." << endl;
    }
}


// Function to mark a task as completed in the list
void markTaskCompleted(vector<Task>& tasks) {
    int index;

    // Precondition: The 'tasks' vector must be accessible and modifiable.
    // Post condition: The specified task's 'completed' status is set to true if the index is valid.

    // Prompt for task number to mark as completed
    cout << "Enter task number to mark as completed: " << endl;
    cin >> index;
    cin.ignore();  // Ignore the newline character after the number input

    // Check if the index is valid
    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;  // Mark the task as completed
        cout << "Task marked as completed." << endl;
    } else {
        // Handle invalid task number
        cout << "Invalid task number." << endl;
    }
}


// Function to display all tasks in the list
void viewTasks(const vector<Task>& tasks) {
    // Precondition: The 'tasks' vector must be accessible and its elements must be readable.
    // Post condition: All tasks and their details are displayed to the user. The completion percentage is also displayed.

    cout << endl << "--- Task List ---" << endl;
    int completedCount = 0;

    // Iterate through all tasks and display their details
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        cout << i + 1 << ". " << task.title << " | Due: " << task.dueDate
             << " | Priority: " << task.priority
             << " | Status: " << (task.completed ? "Completed" : "Pending") << endl;
        if (task.completed) ++completedCount;  // Count completed tasks
    }

    // Calculate and display the completion percentage
    if (tasks.empty()) {
        cout << "Completion Percentage: 0%" << endl;
    } else {
        int completionPercentage = (completedCount * 100) / tasks.size();
        cout << "Completion Percentage: " << completionPercentage << "%" << endl;
    }
}


// Function to save all tasks to a file
void saveTasksToFile(const vector<Task>& tasks) {
    // Precondition: The 'tasks' vector must be accessible and its elements must be readable.
    // Post condition: All tasks in the 'tasks' vector are written to a file named "tasks.txt".

    ofstream outFile("tasks.txt");  // Open the file for writing
    for (size_t i = 0; i < tasks.size(); ++i) {
        // Write each task's details to the file
        outFile << tasks[i].title << endl
                << tasks[i].dueDate << endl
                << tasks[i].priority << endl
                << tasks[i].completed << endl;
    }

    cout << "Tasks saved successfully." << endl;  // Inform the user that tasks have been saved
}


// Function to load tasks from a file
void loadTasksFromFile(vector<Task>& tasks) {
    // Precondition: The file "tasks.txt" must exist and be accessible for reading.
    // Post condition: All tasks from the file "tasks.txt" are loaded into the 'tasks' vector.

    ifstream inFile("tasks.txt");  // Open the file for reading
    if (!inFile) return;  // If the file cannot be opened, exit the function

    Task task;
    while (getline(inFile, task.title)) {
        // Read each task's details from the file
        getline(inFile, task.dueDate);
        inFile >> task.priority >> task.completed;
        inFile.ignore();  // Ignore the newline character after reading the task details
        tasks.push_back(task);  // Add the task to the vector
    }
}


// Function to filter and sort tasks based on user choice
void filterAndSortTasks(vector<Task>& tasks) {
    int choice;

    // Precondition: The 'tasks' vector must be accessible and modifiable.
    // Post condition: Tasks are filtered or sorted based on the user's choice.

    cout << "1. Filter by status (1: Completed, 0: Pending)" << endl;
    cout << "2. Sort by priority" << endl;
    cout << "3. Sort by due date" << endl;
    cout << "Enter your choice: " << endl;
    cin >> choice;
    cin.ignore();  // Ignore the newline character after the number input

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
        // Sort tasks by priority
        for (size_t i = 0; i < tasks.size(); ++i) {
            for (size_t j = i + 1; j < tasks.size(); ++j) {
                if (tasks[i].priority > tasks[j].priority) {
                    swap(tasks[i], tasks[j]);
                }
            }
        }
        cout << "Tasks sorted by priority." << endl;
    } else if (choice == 3) {
        // Sort tasks by due date
        for (size_t i = 0; i < tasks.size(); ++i) {
            for (size_t j = i + 1; j < tasks.size(); ++j) {
                if (tasks[i].dueDate > tasks[j].dueDate) {
                    swap(tasks[i], tasks[j]);
                }
            }
        }
        cout << "Tasks sorted by due date." << endl;
    } else {
        // Handle invalid choice
        cout << "Invalid choice." << endl;
    }
}

