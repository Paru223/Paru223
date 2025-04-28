#include "Scene.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "Scene_Manager.h"
#include "selector_scene.h"
#include "util.h"
#include "Atlas.h"
#include "Animation.h"
#include "platform.h"
#include "player.h"
#include <graphics.h>
#pragma comment(lib,"Winmm.lib")

Camera main_camera;
SceneManager scene_manager;
std::vector<Platform> platform_list;

bool is_debug = false;

IMAGE img_menu_background;

IMAGE img_VS;                // VS��ս��־ͼƬ���������˵�/ѡ�ǽ��棩
IMAGE img_1P;                // "1P"����ͼƬ�����1��ʶ��
IMAGE img_2P;                // "2P"����ͼƬ�����2��ʶ��
IMAGE img_1P_desc;           // ���1��λ˵��ͼ����ʾWSAD�ƶ��Ȳ�����ʾ��
IMAGE img_2P_desc;           // ���2��λ˵��ͼ����ʾ������ƶ��Ȳ�����ʾ��
IMAGE img_gravestone_left;   // ���Ĺ��װ��ͼƬ����������Ԫ�أ�
IMAGE img_gravestone_right;  // �Ҳ�Ĺ��װ��ͼƬ����������Ԫ�أ�

IMAGE img_selector_tip;      // ѡ�ǽ��������ʾ����ͼƬ����"��ȷ�ϼ�ѡ��"��
IMAGE img_selector_background; // ѡ�ǽ��汳��ͼ

// ���1ѡ��ť����ͬ״̬��
IMAGE img_1P_selector_btn_idle_left;    // 1P����ѡ��ťĬ��״̬
IMAGE img_1P_selector_btn_idle_right;   // 1P����ѡ��ťĬ��״̬
IMAGE img_1P_selector_btn_down_left;    // 1P����ѡ��ť����״̬
IMAGE img_1P_selector_btn_down_right;   // 1P����ѡ��ť����״̬

// ���2ѡ��ť����ͬ״̬��
IMAGE img_2P_selector_btn_idle_left;    // 2P����ѡ��ťĬ��״̬
IMAGE img_2P_selector_btn_idle_right;   // 2P����ѡ��ťĬ��״̬
IMAGE img_2P_selector_btn_down_left;    // 2P����ѡ��ť����״̬
IMAGE img_2P_selector_btn_down_right;   // 2P����ѡ��ť����״̬

// ��ɫѡ�񱳾�
IMAGE img_peashooter_selector_background_left;   // �㶹���ֽ�ɫ����ѡ�񱳾�
IMAGE img_peashooter_selector_background_right;  // �㶹���ֽ�ɫ����ѡ�񱳾�
IMAGE img_sunflower_selector_background_left;   // ���տ���ɫ����ѡ�񱳾�
IMAGE img_sunflower_selector_background_right;  // ���տ���ɫ����ѡ�񱳾�

IMAGE img_sky;               // ��ձ���ͼ��
IMAGE img_hills;             // Զɽ����ͼ��
IMAGE img_platform_large;    // ����ƽ̨��ײ��ͼƬ
IMAGE img_platform_small;    // С��ƽ̨��ײ��ͼƬ
IMAGE img_1P_cursor;         // ���1ս����꣨����ָʾλ�ã�
IMAGE img_2P_cursor;         // ���2ս����꣨����ָʾλ�ã�

// �㶹���ֶ���ͼ��
Atlas atlas_peashooter_idle_left;    // �㶹���ֳ�����Ĵ�������ͼ��
Atlas atlas_peashooter_idle_right;   // �㶹���ֳ����ҵĴ�������ͼ��
Atlas atlas_peashooter_run_left;    // �㶹���ֳ�����ı��ܶ���ͼ��
Atlas atlas_peashooter_run_right;   // �㶹���ֳ����ҵı��ܶ���ͼ��
Atlas atlas_peashooter_attack_ex_left;  // �㶹���ֳ���������⹥������ͼ��
Atlas atlas_peashooter_attack_ex_right; // �㶹���ֳ����ҵ����⹥������ͼ��
Atlas atlas_peashooter_die_left;    // �㶹���ֳ��������������ͼ��
Atlas atlas_peashooter_die_right;   // �㶹���ֳ����ҵ���������ͼ��

// ���տ�����ͼ��
Atlas atlas_sunflower_idle_left;    // ���տ�������Ĵ�������ͼ��
Atlas atlas_sunflower_idle_right;   // ���տ������ҵĴ�������ͼ��
Atlas atlas_sunflower_run_left;     // ���տ�������ı��ܶ���ͼ��
Atlas atlas_sunflower_run_right;    // ���տ������ҵı��ܶ���ͼ��
Atlas atlas_sunflower_attack_ex_left;  // ���տ�����������⹥������ͼ��
Atlas atlas_sunflower_attack_ex_right; // ���տ������ҵ����⹥������ͼ��
Atlas atlas_sunflower_die_left;     // ���տ����������������ͼ��
Atlas atlas_sunflower_die_right;    // ���տ������ҵ���������ͼ��

// �ӵ���̫�����
IMAGE img_pea;                      // �㶹�ӵ�ͼƬ
Atlas atlas_pea_break;              // �㶹���鶯��ͼ��
Atlas atlas_sun;                    // ̫������ͼ��
Atlas atlas_sun_explode;            // ̫����ը����ͼ��
Atlas atlas_sun_ex;                 // ����̫������ͼ��
Atlas atlas_sun_ex_explode;         // ����̫����ը����ͼ��
Atlas atlas_sun_text;               // "��"�ı�����ͼ��

// ��Ч����
Atlas atlas_run_effect;             // ������Ч����ͼ��
Atlas atlas_jump_effect;            // ��Ծ��Ч����ͼ��
Atlas atlas_land_effect;            // �����Ч����ͼ��

// ʤ������
IMAGE img_1P_winner;                // 1P ��ʤ�ı�ͼƬ
IMAGE img_2P_winner;                // 2P ��ʤ�ı�ͼƬ
IMAGE img_winner_bar;               // ��ʤ����ı�����ͼƬ

IMAGE img_avatar_peashooter;
IMAGE img_avatar_sunflower;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;

Player* player_1 = nullptr;
Player* player_2 = nullptr;

void flip_altas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0;i < src.get_size();i++)
	{
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}

void load_game_resources()
{
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_VS, _T("resources/VS.png"));

	loadimage(&img_1P, _T("resources/1P.png"));

	loadimage(&img_2P, _T("resources/2P.png"));

	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));

	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));

	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));

	flip_image(&img_gravestone_right, &img_gravestone_left);

	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));

	loadimage(&img_selector_background, _T("resources/selector_background.png"));

	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));

	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);

	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));

	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);

	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));

	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);

	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));

	flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);

	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));

	flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);

	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));

	flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

	loadimage(&img_sky, _T("resources/sky.png"));

	loadimage(&img_hills, _T("resources/hills.png"));

	loadimage(&img_platform_large, _T("resources/platform_large.png"));

	loadimage(&img_platform_small, _T("resources/platform_small.png"));

	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));

	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));



	atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);

	flip_altas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);

	atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);

	flip_altas(atlas_peashooter_run_right, atlas_peashooter_run_left);

	atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);

	flip_altas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);

	atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);

	flip_altas(atlas_peashooter_die_right, atlas_peashooter_die_left);

	atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);

	flip_altas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);

	atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);

	flip_altas(atlas_sunflower_run_right, atlas_sunflower_run_left);

	atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);

	flip_altas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);

	atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);

	flip_altas(atlas_sunflower_die_right, atlas_sunflower_die_left);

	loadimage(&img_pea, _T("resources/pea.png"));

	atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);

	atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);

	atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);

	atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);

	atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);

	atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);

	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);

	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);

	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img_1P_winner, _T("resources/1p_winner.png"));

	loadimage(&img_2P_winner, _T("resources/2p_winner.png"));

	loadimage(&img_winner_bar, _T("resources/winner_bar.png"));

	loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));

	loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);

	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);

	mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);

	mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);

	mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);

	mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);

	mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);

	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);

	mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);

	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);

	mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);

	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);

	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);

	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);

}

int main()
{
	load_game_resources();  // <-- ����λ��
	player_1 = new PeashooterPlayer();  // ȷ���ȳ�ʼ�����
	player_2 = new SunflowerPlayer();   // �� PeashooterPlayer()
	player_1->set_id(playerID::P1);     // �������ID
	player_2->set_id(playerID::P2);
	std::cout << "��Դ�������" << std::endl;
	ExMessage msg;
	const int FPS = 60;

	load_game_resources();

	initgraph(1280, 720);
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	menu_scene = new Menu_scene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);

	Scene* scene = new Menu_scene;

	scene->on_enter();

	while (true)
	{
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.on_draw(main_camera);
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if(frame_delta_time < 1000 / FPS)
		{
			Sleep(1000 / FPS - frame_delta_time);
		}
	}
	EndBatchDraw();


	delete menu_scene;
	delete game_scene;
	delete selector_scene;

	closegraph();
	return 0;
}