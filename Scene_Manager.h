#pragma once
#include <iostream>
#include "Scene.h"

extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* selector_scene;

class SceneManager
{
public:
	enum class Scenetype
	{
		Menu,
		Game,
		Selector
	};

public:
	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}

    void switch_to(Scenetype type) {
        // 防御1：检查当前场景是否有效
        if (current_scene) {
            current_scene->on_exit();
        }

        // 防御2：检查目标场景是否有效
        Scene* target = nullptr;
        switch (type) {
        case Scenetype::Menu: target = menu_scene; break;
        case Scenetype::Game: target = game_scene; break;
        case Scenetype::Selector: target = selector_scene; break;
        }

        if (!target) {
            // 可以添加日志：LOG_ERROR("Attempted to switch to invalid scene");
            return;
        }

        current_scene = target;
        current_scene->on_enter(); // 现在current_scene保证非空
    }

    // 对所有操作添加空检查
    void on_update(int delta) {
        if (current_scene) current_scene->on_update(delta);
    }

    void on_draw(const Camera& camera) {
        if (current_scene) current_scene->on_draw(camera);
    }

    void on_input(const ExMessage& msg) {
        if (current_scene) current_scene->on_input(msg);
    }
private:
	Scene* current_scene = nullptr;
};