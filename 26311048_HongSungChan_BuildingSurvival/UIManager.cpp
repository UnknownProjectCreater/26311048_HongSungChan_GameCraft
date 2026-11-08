#include "UIManager.h"

static UIManager* g_uiManager;

UIManager::UIManager()
{
    g_uiManager = this;
}

UIManager* GetUIManager()
{
    return g_uiManager;
}