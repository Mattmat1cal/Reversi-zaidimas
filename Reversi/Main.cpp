#include <iostream>
#include "GameRendering.h"
#include "testing/TestRunner.h"
void RunTests()
{
	TestRunner runner;
	bool allTestPassed = runner.runAllTests();
	if (allTestPassed) std::cout << "All tests passed!\n";
	else std::cout << "Some tests have failed\n";
	system("pause");
}
int main() 
{
	//RunTests();
	GameRendering renderer;
	renderer.renderMenu();
}