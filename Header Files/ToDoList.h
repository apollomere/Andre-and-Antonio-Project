#ifndef TODOLIST_H
#define TODOLIST_H
class ToDoList
{
private:
	std::vector<Task*> tasks;
	//Antonio add the for loops, I do the function declarations and protoypes and file formatting.
public:
	~ToDoList();
	void addTask(const std::string&title, const std::string&priority, const std::string&due_date);
	void displayTasks(const std::string&sortMethod = "priority") const;
	void saveToFile(const std::string& fileName) const;
	void loadFromFile(const std::string& fileName); //Cannot be constant, as the file would not be able to load preexisting tasks to the file destination.(FIXED)-Andre
};

//Does it make sense to just have header files be abstract classes always?-Andre
#endif