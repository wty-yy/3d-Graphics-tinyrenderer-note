#include <bits/stdc++.h>
#include "tgaimage.h"   // tga画图库
#include "model.h"      // 模型库, 实现模型读取
#include "geometry.h"   // 几何库, 定义顶点数据Vec2和Vec3

const double eps = 1e-5;
const TGAColor white(255, 255, 255);
const TGAColor red(255, 0, 0);
const TGAColor green(0, 255, 0);
const TGAColor blue(0, 0, 255);

const int width = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAColor color, TGAImage &image) {
    bool fg = false;
    if (1.0 * std::abs(y1-y0) / std::abs(x1-x0) > 1) {  // 如果斜率>1, 则根据y轴递增绘制线段, 否则线段不连续, 直接交换x,y轴, 并用fg记录下来
        std::swap(x0, y0);
        std::swap(x1, y1);
        fg = true;
    }
    if (x0 > x1) {  // 保证(x0, y0)在(x1, y1)的左侧
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    for (int x = x0; x <= x1; x++) {
        double t = 1.0 * (x - x0) / (x1 - x0);
        int y = t * y1 + (1-t) * y0;
        if (!fg) image.set(x, y, color);
        else image.set(y, x, color);  // 反转了x,y轴
    }
}

int main() {
    Model *model = new Model("obj/african_head.obj");  // 读取模型
    // Model *model = new Model("obj/monster.obj");  // 读取模型
    TGAImage image(width, width, TGAImage::RGB);  // 创建画布
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            // 取出三角面中相邻的两个顶点
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            // 做变换从 (-1, -1)->(0, 0), (1, 1)->(width, height)
            int x0 = (v0.x+1) * width / 2;
            int x1 = (v1.x+1) * width / 2;
            int y0 = (v0.y+1) * height / 2;
            int y1 = (v1.y+1) * height / 2;
            line(x0, y0, x1, y1, white, image);
        }
    }
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}

// 编译并运行命令:
// g++ 3_model_line.cpp tgaimage.cpp model.cpp -o main && main.exe && output.tga