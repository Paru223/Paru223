#pragma once
#include <graphics.h>
#include "Atlas.h"
#include "util.h"
#include "camera.h"
#include <functional>

class Animation
{
public:
    Animation() = default;  // Ĭ�Ϲ��캯��
    ~Animation() = default; // Ĭ����������

    /**
     * @brief ��ָ��λ�û��Ƶ�ǰ֡
     * @param x ����λ�õ�x����
     * @param y ����λ�õ�y����
     */
    void on_draw(const Camera& camera,int x, int y) const
    {
        putimage_alpha(camera,x, y, atlas->get_image(idx_frame));
    }

    /**
     * @brief ���ö���״̬
     */
    void reset()
    {
        timer = 0;
        idx_frame = 0;
    }

    /**
     * @brief ���ö���ʹ�õ�ͼ��
     * @param new_atlas ָ��Atlas�����ָ��
     */
    void set_atlas(Atlas* new_atlas)
    {
        reset();
        atlas = new_atlas;
    }

    /**
     * @brief �����Ƿ�ѭ������
     * @param flag true��ʾѭ����false��ʾ��ѭ��
     */
    void set_loop(bool flag)
    {
        is_loop = flag;
    }

    /**
     * @brief ����֡���ʱ��(����)
     * @param ms ֡���ʱ��(����)
     */
    void set_interval(int ms)
    {
        interval = ms;
    }

    /**
     * @brief ��ȡ��ǰ֡����
     * @return ��ǰ֡����
     */
    int get_idx_frame()
    {
        return idx_frame;
    }

    /**
     * @brief ��ȡ��ǰ֡ͼ��
     * @return ָ��ǰ֡IMAGE�����ָ��
     */
    IMAGE* get_frame()
    {
        return atlas->get_image(idx_frame);
    }

    /**
     * @brief ��鶯���Ƿ񲥷����
     * @return true��ʾ����ɣ�false��ʾδ���
     * @note ����ѭ���������Ƿ���false
     */
    bool check_finished()
    {
        if (is_loop) return false;
        return (idx_frame == atlas->get_size() - 1);
    }

    /**
     * @brief ���¶���״̬
     * @param delta �����ϴθ��µ�ʱ������(����)
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
                    callback();  // ��ѭ����������ʱ���ûص�����
                }
            }
        }
    }

    /**
     * @brief ���ö��������ص�����
     * @param callback �ص���������
     */
    void set_callback(std::function<void()> callback)
    {
        this->callback = callback;
    }

private:
    int timer = 0;          // ֡��ʱ��(����)
    int interval = 0;       // ֡���ʱ��(����)
    int idx_frame = 0;      // ��ǰ֡����
    bool is_loop = true;    // �Ƿ�ѭ�����ű�־
    Atlas* atlas = nullptr; // ָ�򶯻�ͼ����ָ��
    std::function<void()> callback; // ���������ص�����
};