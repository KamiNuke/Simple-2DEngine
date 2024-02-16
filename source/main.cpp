#include "MainClass.h"

int main(int argc, char* args[])
{
	MainClass* mainclass{ new MainClass{} };

    mainclass->Loop();

	delete mainclass;
	return 0;
}
