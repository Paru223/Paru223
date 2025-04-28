#pragma once
#include <graphics.h>
#include "Atlas.h"
#include "util.h"
#include "camera.h"
#include <functional>

class Animation
{
public:
    Animation() = default;  // 默认构造函数
    ~Animation() = default; // 默认析构函数

    /**
     * @brief 在指定位置绘制当前帧
     * @param x 绘制位置的x坐标
     * @param y 绘制位置的y坐标
     */
    void on_draw(const Camera& camera,int x, int y) const
    {
        putimage_alpha(camera,x, y, atlas->get_image(idx_frame));
    }

    /**
     * @brief 重置动画状态
     */
    void reset()
    {
        timer = 0;
        idx_frame = 0;
    }

    /**
     * @brief 设置动画使用的图集
     * @param new_atlas 指向Atlas对象的指针
     */
    void set_atlas(Atlas* new_atlas)
    {
        reset();
        atlas = new_atlas;
    }

    /**
     * @brief 设置是否循环播放
     * @param flag true表示循环，false表示不循环
     */
    void set_loop(bool flag)
    {
        is_loop = flag;
    }

    /**
     * @brief 设置帧间隔时间(毫秒)
     * @param ms 帧间隔时间(毫秒)
     */
    void set_interval(int ms)
    {
        interval = ms;
    }

    /**
     * @brief 获取当前帧索引
     * @return 当前帧索引
     */
    int get_idx_frame()
    {
        return idx_frame;
    }

    /**
     * @brief 获取当前帧图像
     * @return 指向当前帧IMAGE对象的指针
     */
    IMAGE* get_frame()
    {
        return atlas->get_image(idx_frame);
    }

    /**
     * @brief 检查动画是否播放完成
     * @return true表示已完成，false表示未完成
     * @note 对于循环动画总是返回false
     */
    bool check_finished()
    {
        if (is_loop) return false;
        return (idx_frame == atlas->get_size() - 1);
    }

    /**
     * @brief 更新动画状态
     * @param delta 距离上次更新的时间增量(毫秒)
     */
    void on_update(int delta)
    {
        timer += delta;
        if (timer >= interval)
        {
            timer = 0;
            idx_frame++;
            if (idx_frame >= atlas->get_size())
            {
                idx_frame = is_loop ? 0 : atlas->get_size() - 1;
                if (!is_loop && callback)
                {
                    callback();  // 非循环动画结束时调用回调函数
                }
            }
        }
    }

    /**
     * @brief 设置动画结束回调函数
     * @param callback 回调函数对象
     */
    void set_callback(std::function<void()> callback)
    {
        this->callback = callback;
    }

private:
    int timer = 0;          // 帧计时器(毫秒)
    int interval = 0;       // 帧间隔时间(毫秒)
    int idx_frame = 0;      // 当前帧索引
    bool is_loop = true;    // 是否循环播放标志
    Atlas* atlas = nullptr; // 指向动画图集的指针
    std::function<void()> callback; // 动画结束回调函数
};