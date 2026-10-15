#include <glc2d.h>

#if defined(_DEBUG)
    #if defined(_M_X64)
        #pragma comment(lib, "glc2d_x64_debug.lib")
    #elif defined(_M_IX86)
        #pragma comment(lib, "glc2d_win32_debug.lib")
    #endif
#else
    #if defined(_M_X64)
        #pragma comment(lib, "glc2d_x64_release.lib")
    #elif defined(_M_IX86)
        #pragma comment(lib, "glc2d_win32_release.lib")
    #endif
#endif

#include <stdio.h>
#include "GraphicEngine.h"
#include "App.h"

int GraphicEngine::Update()
{
    return g_pApp->Update();
}

int GraphicEngine::Render()
{
    return g_pApp->Render();
}

int GraphicEngine::Init()
{
    auto hr = g2_InitSdk();
    if (0 > hr)
        return -1;

    g2_SetFrameMove(Update);
    g2_SetRender(Render);

	g2_CreateWin();

	return 0;
}

void GraphicEngine::Destroy()
{
	g2_DestroyWin();
}

int GraphicEngine::Run()
{
	auto r = g2_Run();
	return r;
}