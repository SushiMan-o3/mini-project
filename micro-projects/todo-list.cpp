#include <iostream>
#include <vector>

using namespace std;

bool programRunning = true; // global variable to control the program loop

struct Task {
    string description;
    bool completed;
};

std::vector<Task> toDoList; // global dynamic array to store to do

void help();
bool addTask();
void removeTask();
void listTasks();
void completeTask();

void help(){
    std::cout << "Commands: " << std::endl;
    std::cout << "add - Add a new task to the list" << std::endl;
    std::cout << "remove - Remove a task from the list" << std::endl;
    std::cout << "list - List all tasks" << std::endl;
    std::cout << "complete - Mark a task as completed" << std::endl;
    std::cout << "quit - Exit the program" << std::endl;
}


int main() {
    std::cout << "Welcome to your to-do list. Type help for a list of commands" << std::endl;

    string userInput;

    do {
        std::cin >> userInput;

        if (userInput == "help") {
            help();
        }
        else if (userInput == "quit"){
            programRunning = false;
        }
        else if (userInput == "add") {
            addTask();
        }
        else if (userInput == "remove") {
            removeTask();
        }
        else if (userInput == "list") {
            listTasks();
        }
        else if (userInput == "complete") {
            completeTask();
        }
        else {
            std::cout << "Invalid command. Type help for a list of commands" << std::endl;
        }

    } while (programRunning);

    return 0;
}


bool addTask(){
    std::cin.ignore(); // discard leftover newline left behind by the previous cin >>
    string description;
    std::cout << "Enter the task description: ";
    std::getline(std::cin, description);

    toDoList.push_back(Task{description, false});
    std::cout << "Task added." << std::endl;
    return true;
}


void removeTask(){
    if (toDoList.empty()) {
        std::cout << "No tasks to remove." << std::endl;
        return;
    }

    listTasks();
    std::cout << "Enter the number of the task to remove: ";
    int index;
    std::cin >> index;

    if (index < 1 || index > static_cast<int>(toDoList.size())) {
        std::cout << "Invalid task number." << std::endl;
        return;
    }

    toDoList.erase(toDoList.begin() + (index - 1));
    std::cout << "Task removed." << std::endl;
}


void listTasks(){
    if (toDoList.empty()) {
        std::cout << "Your to-do list is empty." << std::endl;
        return;
    }

    for (size_t i = 0; i < toDoList.size(); i++) {
        std::cout << i + 1 << ". [" << (toDoList[i].completed ? "x" : " ") << "] "
                   << toDoList[i].description << std::endl;
    }
}


void completeTask(){
    if (toDoList.empty()) {
        std::cout << "No tasks to complete." << std::endl;
        return;
    }

    listTasks();
    std::cout << "Enter the number of the task to mark as completed: ";
    int index;
    std::cin >> index;

    if (index < 1 || index > static_cast<int>(toDoList.size())) {
        std::cout << "Invalid task number." << std::endl;
        return;
    }

    toDoList[index - 1].completed = true;
    std::cout << "Task marked as completed." << std::endl;
}
