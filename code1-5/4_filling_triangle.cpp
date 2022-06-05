#include <bits/stdc++.h>
#include "tgaimage.h"   // tga画图库
#include "model.h"      // 模型库, 实现模型读取
#include "geometry.h"   // 几何库, 定义顶点数据Vec2和Vec3

const double eps = 1e-5;
const TGAColor white(255, 255, 255);
const TGAColor red(255, 0, 0);
const TGAColor green(0, 255, 0);
const TGAColor blue(0, 0, 255);

void line(Vec2i v0, Vec2i v1, TGAColor color, TGAImage &image) {
    bool fg = false;
    if (1.0 * std::abs(v1.y-v0.y) / std::abs(v1.x-v0.x) > 1) {  // 如果斜率>1, 则根据y轴递增绘制线段, 否则线段不连续, 直接交换x,y轴, 并用fg记录下来
        std::swap(v0.x, v0.y);
        std::swap(v1.x, v1.y);
        fg = true;
    }
    if (v0.x > v1.x) {  // 保证(x0, y0)在(x1, y1)的左侧
        std::swap(v0, v1);
    }
    for (int x = v0.x; x <= v1.x; x++) {
        double t = 1.0 * (x - v0.x) / (v1.x - v0.x);
        int y = t * v1.y + (1-t) * v0.y;
        if (!fg) image.set(x, y, color);
        else image.set(y, x, color);  // 反转了x,y轴
    }
}

void fill(Vec2i v0, Vec2i v1, Vec2i v2, TGAColor color, TGAImage &image, bool outline=false) {
    if (v0.y == v1.y && v0.y == v2.y) return;  // 如果y轴相等则无法填充颜色
    // 简单冒泡排序, 使得 v0.y < v1.y < v2.y
    if (v0.y > v1.y) std::swap(v0, v1);
    if (v0.y > v2.y) std::swap(v0, v2);
    if (v1.y > v2.y) std::swap(v1, v2);
    Vec2i vt = v0;  // 存储当前(x1,y1)连接的顶点
    for (int y = v0.y; y <= v2.y; y++) {
        int l = v0.x + 1.0 * (y - v0.y) / (v2.y - v0.y) * (v2.x - v0.x);
        if (y > v1.y || v0.y == v1.y) vt = v2;  // 扫过中间点时或v0和v1的y坐标相同时, 交换(x1,y1)连接的顶点, 避免除以0导致程序错误
        int r = v1.x + 1.0 * (y - v1.y) / (vt.y - v1.y) * (vt.x - v1.x);
        if (l > r) std::swap(l, r);
        for (int x = l; x <= r; x++) image.set(x, y, color);
    }
    if (outline) {  // 绘制轮廓线
        line(v0, v1, red, image);
        line(v0, v2, red, image);
        line(v1, v2, red, image);
    }
}

int main() {
    TGAImage image(100, 100, TGAImage::RGB);
    Vec2i v0 = Vec2i(0, 0), v1 = Vec2i(50, 30), v2 = Vec2i(20, 50);
    fill(v0, v1, v2, white, image, true);
    v0 = Vec2i(30, 50), v1 = Vec2i(80, 40), v2 = Vec2i(50, 90);
    fill(v0, v1, v2, blue, image, true);
    v0 = Vec2i(99, 0), v1 = Vec2i(80, 10), v2 = Vec2i(90, 90);
    fill(v0, v1, v2, green, image, true);
    v0 = Vec2i(0, 99), v1 = Vec2i(20, 80), v2 = Vec2i(5, 50);
    fill(v0, v1, v2, blue, image, false);
    image.write_tga_file("output.tga");
    return 0;
}

// 编译并运行命令:
// g++ 4_filling_triangle.cpp tgaimage.cpp model.cpp -o main && main.exe && output.tga