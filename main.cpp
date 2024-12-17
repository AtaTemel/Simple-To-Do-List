#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void ShowMenu();



struct TaskProperties {
    string name;
    int priority;
    bool IsCompleted;
    int DueDate;
};
vector<TaskProperties> tasks;
int main() {
ShowMenu();
}
void ShowMenu() {
    cout << endl <<"TO-DO LIST MANAGER";
    cout << endl <<"1-Add New Task";
    cout << endl <<"2-Edit Task";
    cout << endl <<"3-Delete Task";
    cout << endl <<"4-Mark Task ";
    cout << endl <<"Choose one option ";
    cout << endl <<"You have "<< tasks.capacity() << " tasks" << endl;
}
void AddNewTask() {

}
void EditTask() {

}
void DeleteTask() {

}
void MarkTask() {

}
void ShowTask() {

}
void LoadTasksFromFile(vector<TaskProperties> task_properties ) {
    ifstream InFile ("TaskProperties.txt");
}