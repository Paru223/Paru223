#pragma once
#include "Scene.h" // 包含场景基类的头文件
#include "Scene_Manager.h" // 包含场景管理器的头文件
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern IMAGE img_menu_background;
extern SceneManager scene_manager;

// 定义菜单场景类，继承自场景基类
class Menu_scene : public Scene
{
public:
	// 默认构造函数
	Menu_scene() = default;

	// 默认析构函数
	~Menu_scene() = default;

	// 场景进入时的处理函数
	void on_enter()
	{
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
	}

	// 场景更新函数，每帧调用
	void on_update(int delta)
	{

	}

	// 场景绘制函数
	void on_draw(const Camera& camera)
	{
		putimage(0, 0, &img_menu_background);
	}

	// 场景输入处理函数
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYUP)
		{
			mciSendString(_T("play ui_confirm repeat from 0"), NULL, 0, NULL);
			scene_manager.switch_to(SceneManager::Scenetype::Selector);
		}
	}

	// 场景退出时的处理函数
	void on_exit()
	{

	}

private:

};