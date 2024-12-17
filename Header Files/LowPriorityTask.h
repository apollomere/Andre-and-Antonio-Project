#ifndef LOWPRIORITYTASK_H
#define LOWPRIORITYTASK_H
class LowPriorityTask :public Task
{
public:
	LowPriorityTask(const std::string&title, const std::string&priority, const std::string&due_date_string);

	std::string priorityLevel() const override;

	void display()const override;
};
#endif

//This is the 2nd variant derived from task-Andre
//This is supposed to be the function to be set when the user chooses low.