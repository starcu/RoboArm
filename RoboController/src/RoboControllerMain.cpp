#include <iostream>
#include "RoboController.h"

int main(int argc, char const *argv[])
{
	auto robo = Robo::get();
	while(robo->getCurrentState() == RoboState::OK)
	{
		RoboLogger::logger()->timed_log(normal, 30000, "RoboWorker status: " + RoboStateToString(robo->getCurrentState()));
	}

	return 0;
}