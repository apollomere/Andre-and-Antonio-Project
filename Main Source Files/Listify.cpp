//Driver Code; Where the magic happens
#include "Task.h"
#include "HighPriorityTask.h"
#include "LowPriorityTask.h"
#include "ToDoList.h"
int main() {
    system("color a");
    ToDoList to_do_list; //Instantiation
    const std::string fileName = "tasks.txt"; //file name intitialized.

        to_do_list.loadFromFile(fileName);

    while (true) 
    {
        std::cout << "\nListify To-Do List" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. View Tasks (Sort by Priority)" << std::endl;
        std::cout << "3. View Tasks (Sort by Due Date)" << std::endl;
        std::cout << "4. Delete Tasks" << std::endl;
        std::cout << "5. Save and Exit" << std::endl;

        std::string userInput;
        std::cout << "Choose an option: ";
        std::cin >> userInput;
        //user control-antonio
        if (userInput == "1") 
        {
            try 
            {
                std::string title, priority, due_date;
                std::cin.ignore();
                std::cout << "Enter task title: ";
                std::getline(std::cin, title);
                std::cout << "Enter priority (high/low): ";
                std::cin >> priority;
                std::cout << "Enter due date (YYYY-MM-DD): ";
                std::cin >> due_date;

                to_do_list.addTask(title, priority, due_date);
                std::cout << "\nTask added successfully.";
            }
            catch (std::exception&addTaskErr) 
            {
                std::cout << "\nException Error: " << &addTaskErr;
            }

        }
        else if (userInput == "2") 
        {
            std::cout << "\nTasks sorted by priority:\n" << std::endl;
            to_do_list.displayTasks("priority");

        }
        else if (userInput == "3") 
        {
            std::cout << "\nTasks sorted by due date:\n";
            to_do_list.displayTasks("due_date");

        }
        else if (userInput == "4") 
        {
            std::cout << "\nTask Deletion\n";

        }
        else if (userInput == "5") 
        {
            try 
            {
                to_do_list.saveToFile(fileName);
                std::cout << "\nTasks saved";
                break;
            }
            catch (std::exception&fileSaveError) 
            {
                std::cerr << "\nException Error: " << &fileSaveError;
            }

        }
        else 
        {
            std::cout << "\nInvalid choice. Please try again.";
        }
    }

    return 0;
}