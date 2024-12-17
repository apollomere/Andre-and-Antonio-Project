#include "Task.h"
#include "HighPriorityTask.h"
#include "LowPriorityTask.h"
#include "ToDoList.h"
//Task Baseclass Protected Member Definitions

std::tm Task::timeToStringConversion(const std::string&due_date_string)//Antonio and Andre
{
	try
	{
		tm Date = {};
		std::istringstream streamDate(due_date_string);
		//istringstream converts a specified datatype to be read as a string literal(below)-Andre
		streamDate >> std::get_time(&Date, "%Y-%m-%d");//By reference, why is the year restricted to capital?-Andre
		//Date is read to byte stream as a string literal via get_time(iomanip format that can only be accessed with ctime(EXCLUSIVE))
		if (streamDate.fail())//If stream byte read fails-antonio
		{
			throw std::invalid_argument("\nTime to string conversion error");
		}
		else
		{
			return Date;
		}
	}
	catch (std::exception& timeToStringErr) //Should follow a set exception standard if unsure of a custom one like this for future reference-Andre.
	{
		std::cerr << "\nException Error: " << &timeToStringErr;
	}
}
//NOTE: We need to fix the values in our parameters using direct attribute references in parameters-Andre
//Task Baseclass Public Member Definitions
Task::Task(const std::string&title, const std::string&due_date_string) :title(title) /*due_date{due_date}*/
{
	due_date = timeToStringConversion(due_date_string);
}
Task::~Task()
{
}//getter functions
std::tm Task::getDueDate() const
{
	return due_date;//Problem: When trying to run, it needs to return a string literal from the text file, not from an object method-Andre(Fixed)
}
std::string Task::getTitle() const 
{
	return title; //Added this because there was problems with this not being copied to the file and object(Seems to have fixed it)-Andre
}
void Task::display() const
{
	std::cout << "Task: " << title << ", Due: " << std::put_time(&due_date, "%y-%m-%d") << std::endl;
}



//HighPriorityTask Child Class Member Definitions-antonio
HighPriorityTask::HighPriorityTask(const std::string&title, const std::string&priority, const std::string&due_date_string) :Task(title, due_date_string)
{
}
std::string HighPriorityTask::priorityLevel() const
{
	return "high";
}
void HighPriorityTask::display() const
{
	std::cout << "[High Priority]" << std::endl;
	Task::display();
}

//LowPriorityTask Child Class Member Definitions-Andre
LowPriorityTask::LowPriorityTask(const std::string&title, const std::string&priority,const std::string&due_date_string) :Task(title, due_date_string)
{
}
std::string LowPriorityTask::priorityLevel() const
{
	return "low";
}
void LowPriorityTask::display() const
{
	std::cout << "[Low Priority]" << std::endl;
	Task::display();
}

//ToDoList Base Class Member Definitions-antonio
ToDoList::~ToDoList()
{
	//What this does is loop through entire vector and delete the instance of the object/task?-Andre
	for (Task* currentTask : tasks)
	{
		delete currentTask;
	}
}
void ToDoList::addTask(const std::string&title, const std::string&priority, const std::string&due_date)
{
		Task* currentTask = nullptr;//Prevent wildcard pointers/memory leak
		try
		{
		if (priority == "high")
		{
			currentTask = new HighPriorityTask(title, priority, due_date);
		}
		else if (priority == "low")
		{
			currentTask = new LowPriorityTask(title, priority,due_date);
		}
		else
		{
			throw std::invalid_argument("Invalid priority level");
		}
		try {
			for (Task* allExistingTasks : tasks)//forloop for all tasks-antonio
			{
				tm allExistingTasksDueDate = allExistingTasks->getDueDate();
				tm currentTaskDueDate = currentTask->getDueDate();
				if (std::difftime(mktime(&allExistingTasksDueDate), mktime(&currentTaskDueDate)) == 0)//From ctime, basically this is supposed to get the difference between two dates, if it's 0, they're the same(it's more complex because it uses mktime which converts it to an integer-based value, I'll explain it-Andre
				{
					delete currentTask;
					throw std::invalid_argument("Scheduling Conflict"); 
				}
			}
		}
		catch (std::exception& dueDateErr) //exceptiona hadling for the scheduling conflict-Andre
		{
			std::cerr << "\n Exception Erorr: " << &dueDateErr;
		}
		}
	catch (std::exception& priorityLevelErr)//exception if the program fails with invalid priority level-antonio
	{
		std::cerr << "\nException Error: " << &priorityLevelErr;
	}
	tasks.push_back(currentTask);
}

void ToDoList::displayTasks(const std::string&sortMethod) const
{
	std::vector<Task*> sortedTasks = tasks;
	try
	{
		if (sortMethod == "priority")
		{//Dead spot
			std::sort(sortedTasks.begin(), sortedTasks.end(), [](Task* a, Task* b) { //sorting algorithm-antonio
				return a->priorityLevel() > b->priorityLevel(); //Problem: We only have 2 High and low, multiple tasks tagged with high will shift, we should have task titles be sorted alphanumerically regardless.-Andre
				}); //This is comparing strings, so how does it know High Priority is added to the back first? due to the 1st ASCII character, H, coming before L.-Andre(fixed)
		}
		else if (sortMethod == "due_date")
		{
			std::sort(sortedTasks.begin(), sortedTasks.end(), [](Task* a, Task* b)
				{//sorting algorithm-antonio
					tm aDueDate = a->getDueDate();//Dead spot-Andre(FIXED)
					tm bDueDate = b->getDueDate();
					return difftime(mktime(&aDueDate), mktime(&bDueDate)) < 0; //Positional comparison-Andre
				});
		}
		//else if(file.)
		else
		{
			throw std::invalid_argument("Invalid sorting option");
		}
	}
	catch (std::exception& sortError)
	{
		std::cerr << "\nException Error:" << &sortError;
	}

	for (Task* task : sortedTasks)
	{ //Loops through the sorted tasks and then displays them for the user.
		task->display();
	}
}

void ToDoList::saveToFile(const std::string&fileName) const
{
	std::ofstream file(fileName); //ofstream class for writing
	try {
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file for writing.");
		}
	}
	catch (std::runtime_error& fileOpenErr)
	{
		std::cerr << "\nException Error: " << &fileOpenErr;
	}
	//Note: Heavy use of iomanip library below for convenient format purposes: I wonder if there was a better way we could have this?-Andre
	for (Task* task : tasks) { //The alternative way to loop through all tasks derived from Task: More work for this.
		file << task->getTitle()<<"|" << task->priorityLevel() << "|" << task->getDueDate().tm_year + 1900 << "-"//'tm' prefixes from ctime library due to due_date using tm oriented datatype as attribute(struct)-Andre
			<< std::setfill('0') << std::setw(2) << task->getDueDate().tm_mon + 1 << "-" //might rechange the value range for year and month-Andre
			<< std::setfill('0') << std::setw(2) << task->getDueDate().tm_mday << "|" << std::endl;
	}
	file.close();
}

void ToDoList::loadFromFile(const std::string&fileName)
{
	std::ifstream file(fileName); //Reads to the console of the preexisting file of tasks.-Andre
	try {
		if (!file.is_open()) {
			throw std::runtime_error("Could not open file for reading.");
		}
	}
	catch (std::runtime_error& fileLoadErr)
	{
		std::cerr << "\nException Error: " << &fileLoadErr;
	}
	std::string taskSource;
	while (getline(file, taskSource)) {  //for text file-antonio
		std::stringstream streamTask(taskSource); 
		std::string title, priority, due_date; //Iomanipulation format for design and UI design

		std::getline(streamTask, title, '|');
		std::getline(streamTask, priority, '|');
		std::getline(streamTask, due_date, '|');

		addTask(title, priority, due_date);
		//std::cout << "\n" << title << priority << due_date << std::endl;
		//std::cout << "\n" << title; //So after bugfixing we need to include the title, hmm, the format is priority-date-priority, is it the two children classes?(Fixed)
	}
	std::cout << "\nLoaded saved tasks." << std::endl;

	file.close();
}