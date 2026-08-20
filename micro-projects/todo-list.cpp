#include <iostream>
#include <vector>

using namespace std;

bool programRunning = true; // global variable to control the program loop
std::vector<string> toDoList; // global dynamic array to store to do

void help(){
    std::cout << "Commands: " << std::endl;
    std::cout << "add - Add a new task to the list" << std::endl;
    std::cout << "remove - Remove a task from the list" << std::endl;
    std::cout << "list - List all tasks" << std::endl;
    std::cout << "exit - Exit the program" << std::endl;
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
        } else {
            std::cout << "Invalid command. Type help for a list of commands" << std::endl;
        }
        
    } while (programRunning);
    
    return 0;
}


