#pragma once
#include <glc2d.h>

class GraphicEngine
{
	// Base Func
public:
	struct GameWindow
	{
		int m_x, m_y;
		int m_screenWidth, m_screenHeight;
		CSTR m_screenName;
		bool m_bWindowed;
		float m_screenScale;
	};

	int Init(GameWindow* window);
	void Destroy();

	int Run();

	static int Update();
	static int Render();

	void SetColor(unsigned long color) { g2_SetClearColor(color); };
};