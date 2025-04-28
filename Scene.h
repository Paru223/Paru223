#pragma once
#include <iostream>
#include <graphics.h>
#include "camera.h"

class Scene
{
public:
	Scene();
	virtual void on_enter() { }
	virtual void on_update(int delta) { }//处理数据
	virtual void on_draw(const Camera& camera) {}//渲染绘图
	virtual void on_input(const ExMessage& msg) { }//处理场景
	virtual void on_exit() { }
	~Scene();
private:

};
