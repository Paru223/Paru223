#pragma once
#include <iostream>
#include "camera.h"
#include "vector2.h"
#include "Animation.h"
#include "player_id.h"
#include <graphics.h>

class Player
{
    friend class PeashooterPlayer;
    friend class SunflowerPlayer;
public:
    Player()
    {
        current_animation = &animation_idle_right;
    }
    ~Player() = default;

    virtual void on_update(int delta)
    {
        int direction = is_right_key_down - is_left_key_down;

        // ����λ��
        if (direction != 0)
        {
            position.x += direction * run_velocity * delta;
            is_facing_right = direction > 0;
            current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
        }
        else
        {
            current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        }

        current_animation->on_update(delta);
    }

    virtual void on_draw(const Camera& camera)
    {
        std::cout << "Drawing at X: " << position.x << std::endl;
        current_animation->on_draw(camera, (int)position.x, (int)position.y);
    }

    virtual void on_input(const ExMessage& msg)
    {
        switch (msg.message)
        {
        case WM_KEYDOWN:
            switch (id)
            {
            case playerID::P1:
                switch (msg.vkcode)
                {
                case 0x41: // 'A' ��
                    is_left_key_down = true;
                    break;
                case 0x44: // 'D' ��
                    is_right_key_down = true;
                    break;
                    // ��Ӷ����ҷ�����Ĵ�����ʹ Player 1 ��ʹ�����ǣ�����δ��������
                case VK_LEFT:
                    break;
                case VK_RIGHT:
                    break;
                }
                break;

            case playerID::P2:
                switch (msg.vkcode)
                {
                case VK_LEFT:
                    is_left_key_down = true;
                    break;
                case VK_RIGHT:
                    is_right_key_down = true;
                    break;
                    // ��Ӷ� 'A' �� 'D' ���Ĵ�����ʹ Player 2 ��ʹ�����ǣ�����δ��������
                case 0x41:
                    break;
                case 0x44:
                    break;
                }
                break;
            }
            break;

        case WM_KEYUP:
            switch (id)
            {
            case playerID::P1:
                switch (msg.vkcode)
                {
                case 0x41: // 'A' ��
                    is_left_key_down = false;
                    break;
                case 0x44: // 'D' ��
                    is_right_key_down = false;
                    break;
                    // ��Ӷ����ҷ�����Ĵ���
                case VK_LEFT:
                    break;
                case VK_RIGHT:
                    break;
                }
                break;

            case playerID::P2:
                switch (msg.vkcode)
                {
                case VK_LEFT:
                    is_left_key_down = false;
                    break;
                case VK_RIGHT:
                    is_right_key_down = false;
                    break;
                    // ��Ӷ� 'A' �� 'D' ���Ĵ���
                case 0x41:
                    break;
                case 0x44:
                    break;
                }
                break;
            }
            break;
        }
    }

    void set_id(playerID id)
    {
        this->id = id;
    }

    void set_position(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    Vector2 get_position() const
    {
        return position;
    }

private:
    Vector2 position; // ��ɫλ��
    Animation animation_idle_left; // �������Ĭ�϶���
    Animation animation_idle_right; // �����ҵ�Ĭ�϶���
    Animation animation_run_left; // ������ı��ܶ���
    Animation animation_run_right; // �����ҵı��ܶ���
    Animation* current_animation = nullptr;

    playerID id = playerID::P1;

    const float run_velocity = 0.55f; // �ƶ��ٶ�

    bool is_left_key_down = false;
    bool is_right_key_down = false;

    bool is_facing_right = true;
};