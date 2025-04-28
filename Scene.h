#pragma once
#include <iostream>
#include <graphics.h>
#include "camera.h"

class Scene
{
public:
	Scene();
	virtual void on_enter() { }
	virtual void on_update(int delta) { }//��������
	virtual void on_draw(const Camera& camera) {}//��Ⱦ��ͼ
	virtual void on_input(const ExMessage& msg) { }//������
	virtual void on_exit() { }
	~Scene();
private:

};
