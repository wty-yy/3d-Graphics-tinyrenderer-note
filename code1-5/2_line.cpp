#include <bits/stdc++.h>
#include "tgaimage.h"

const double eps = 1e-5;
const TGAColor white(255, 255, 255);
const TGAColor red(255, 0, 0);
const TGAColor green(0, 255, 0);
const TGAColor blue(0, 0, 255);

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
int main1() {
    TGAImage image(30, 30, TGAImage::RGB);
    line(0, 0, 29, 10, white, image);
    line(29, 11, 26, 29, red, image);
    image.write_tga_file("output.tga");
    return 0;
}

int main() {
    TGAImage image(100, 100, TGAImage::RGB);
    line(0, 1, 99, 20, white, image);
    line(99, 21, 0, 40, red, image);
    line(99, 21, 90, 99, blue, image);
    line(99, 21, 0, 99, green, image);
    image.write_tga_file("output.tga");
    return 0;
}

// 编译并运行命令:
// g++ 2_line.cpp tgaimage.cpp model.cpp -o main && main.exe && output.tga