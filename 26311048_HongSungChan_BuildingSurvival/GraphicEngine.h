#pragma once
#include <glc2d.h>

class GraphicEngine
{
	// Base Func
public:
	struct GameWindow
	{
		int x, y;
		int screenWidth, screenHeight;
		CSTR screenName;
		bool bWindowed;
		float screenScale;
	};

	int Init();
	void Destroy();

	int Run();

	static int Update();
	static int Render();

	void SetColor(unsigned long color) { g2_SetClearColor(color); };
};