#pragma once
#include <graphics.h>
#include "camera.h"
#pragma comment(lib,"MSIMG32.LIB")

inline void flip_image(IMAGE* src, IMAGE* dst)
{
    int w = src->getwidth();
    int h = src->getheight();
    Resize(dst, w, h);
    DWORD* src_buffer = GetImageBuffer(src);
    DWORD* dst_buffer = GetImageBuffer(dst);
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int idx_src = y * w + x;
            int idx_dst = y * w + (w - x - 1);
            dst_buffer[idx_dst] = src_buffer[idx_src];
        }
    }
}

// 版本1：完整绘制图像（带相机偏移）
inline void putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img)
{
    if (!img) return;
    int w = img->getwidth();
    int h = img->getheight();
    const Vector2& pos_camera = camera.get_position();
    AlphaBlend(
        GetImageHDC(GetWorkingImage()),
        (int)(dst_x - pos_camera.x),
        (int)(dst_y - pos_camera.y),
        w, h,
        GetImageHDC(img),
        0, 0, w, h,
        { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

// 版本2：完整绘制图像（不带相机偏移）
inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
    if (!img) return;
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(
        GetImageHDC(GetWorkingImage()),
        dst_x, dst_y,
        w, h,
        GetImageHDC(img),
        0, 0, w, h,
        { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

// 版本3：部分绘制图像（不带相机偏移）
inline void putimage_alpha(int dst_x, int dst_y, int dst_w, int dst_h, IMAGE* img, int src_x, int src_y)
{
    if (!img) return;
    AlphaBlend(
        GetImageHDC(GetWorkingImage()),
        dst_x, dst_y,
        dst_w, dst_h,
        GetImageHDC(img),
        src_x, src_y, dst_w, dst_h,
        { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
    );
}

inline void line(const Camera& camera, int x1, int y1, int x2, int y2)
{
    const Vector2& pos_camera = camera.get_position();
    line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y), (int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y));
}