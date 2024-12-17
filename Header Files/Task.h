#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <ctime>
#include<stdlib.h>
class Task
{
protected: //Implementation for attributes-Andre
	std::string title;
	std::tm due_date;
	std::tm timeToStringConversion(const std::string&due_date_string); //For the ctime library, meetup for discussion-Andre

public:
	Task(const std::string& title, const std::string&due_date_string); //Antonio add Basic class constructor for methods, as well as virtual functions

	virtual ~Task();

	virtual std::string priorityLevel() const = 0;

	std::tm getDueDate() const; //Added dueDate gett function-Andre

	std::string getTitle() const;//Gett function for title-Andre

	virtual void display() const; //display virtual function-antonio
};
#endif