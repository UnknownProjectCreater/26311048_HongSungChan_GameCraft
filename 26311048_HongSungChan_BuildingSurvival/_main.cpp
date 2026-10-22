#include <iostream>
#include "glc2d.h"
#include "App.h"

using namespace std;

int main()
{
	App app;
	if (0 > g_pApp->Init())
		return -1;

	auto rh = g_pApp->Run();

	return 0;
}