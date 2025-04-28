#pragma once
#include "Scene.h" // �������������ͷ�ļ�
#include "Scene_Manager.h" // ����������������ͷ�ļ�
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern IMAGE img_menu_background;
extern SceneManager scene_manager;

// ����˵������࣬�̳��Գ�������
class Menu_scene : public Scene
{
public:
	// Ĭ�Ϲ��캯��
	Menu_scene() = default;

	// Ĭ����������
	~Menu_scene() = default;

	// ��������ʱ�Ĵ�����
	void on_enter()
	{
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
	}

	// �������º�����ÿ֡����
	void on_update(int delta)
	{

	}

	// �������ƺ���
	void on_draw(const Camera& camera)
	{
		putimage(0, 0, &img_menu_background);
	}

	// �������봦����
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYUP)
		{
			mciSendString(_T("play ui_confirm repeat from 0"), NULL, 0, NULL);
			scene_manager.switch_to(SceneManager::Scenetype::Selector);
		}
	}

	// �����˳�ʱ�Ĵ�����
	void on_exit()
	{

	}

private:

};