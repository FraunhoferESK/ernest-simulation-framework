#include <ernest/ernest_addition.hpp>
#include <ernest/scheduler.hpp>
#include <ernest/time.hpp>
#include <ernest/task.hpp>
#include <ernest/simulator.hpp>


namespace ERNEST
{

void Scheduler::Update()
{
	Time execution_budget = milliseconds(1);
	Task* running_task;

	running_task = Schedule();

	// Execute Task
	if (running_task != nullptr) {
		running_task->Execute(execution_budget);
	} else {
		Simulator::Wait(execution_budget);
	}
}

} //namespace ERNEST
