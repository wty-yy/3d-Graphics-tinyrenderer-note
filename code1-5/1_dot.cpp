#include <bits/stdc++.h>
#include "tgaimage.h"

const TGAColor white(255, 255, 255);
const TGAColor red(255, 0, 0);
const TGAColor green(0, 255, 0);
const TGAColor blue(0, 0, 255);

int main() {
    TGAImage image(6, 6, TGAImage::RGB);
    image.set(0, 0, red);
    image.set(5, 5, blue);
    image.set(0, 5, green);
    image.set(5, 0, white);
    image.write_tga_file("output.tga");
    return 0;
}

int main1() {
    TGAImage image(6, 6, TGAImage::RGB);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if ((i + j) & 1) {
                image.set(i, j, red);
            } else {
                image.set(i, j, white);
            }
        }
    }
    // image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}

// 编译并运行命令:
// g++ 1_dot.cpp tgaimage.cpp model.cpp -o main && main.exe && output.tga