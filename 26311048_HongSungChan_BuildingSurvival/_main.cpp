#include <iostream>
#include "glc2d.h"
#include "App.h"

using namespace std;

App* g_pApp;

int main()
{
	App app;
	g_pApp = &app;

	if (0 > g_pApp->Run())
		return -1;

	return 0;
}