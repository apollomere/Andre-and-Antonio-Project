#ifndef HIGHPRIORITYTASK_H
#define HIGHPRIORITYTASK_H
class HighPriorityTask :public Task
{
public:
	HighPriorityTask(const std::string&title, const std::string&priority,const std::string&due_date_string);

	std::string priorityLevel() const override; //It's a string for the return,-Andre

	void display() const override; //override function for HighPriorityTask - Antonio
};
#endif