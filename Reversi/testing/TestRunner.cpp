#include "TestRunner.h"

bool TestRunner::runAllTests()
{
	Catch::Session session;
	return session.run() == 0;
}