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

        // 更新位置
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
                case 0x41: // 'A' 键
                    is_left_key_down = true;
                    break;
                case 0x44: // 'D' 键
                    is_right_key_down = true;
                    break;
                    // 添加对左右方向键的处理，即使 Player 1 不使用它们，避免未处理的情况
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
                    // 添加对 'A' 和 'D' 键的处理，即使 Player 2 不使用它们，避免未处理的情况
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
                case 0x41: // 'A' 键
                    is_left_key_down = false;
                    break;
                case 0x44: // 'D' 键
                    is_right_key_down = false;
                    break;
                    // 添加对左右方向键的处理
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
                    // 添加对 'A' 和 'D' 键的处理
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
    Vector2 position; // 角色位置
    Animation animation_idle_left; // 朝向左的默认动画
    Animation animation_idle_right; // 朝向右的默认动画
    Animation animation_run_left; // 朝向左的奔跑动画
    Animation animation_run_right; // 朝向右的奔跑动画
    Animation* current_animation = nullptr;

    playerID id = playerID::P1;

    const float run_velocity = 0.55f; // 移动速度

    bool is_left_key_down = false;
    bool is_right_key_down = false;

    bool is_facing_right = true;
};