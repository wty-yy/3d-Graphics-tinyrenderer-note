#include <bits/stdc++.h>
#include "tgaimage.h"   // tga画图库
#include "model.h"      // 模型库, 实现模型读取
#include "geometry.h"   // 几何库, 定义顶点数据Vec2和Vec3
#define vd std::vector<double>
#define vdd std::vector<vd>

const double eps = 1e-5;
const TGAColor white(255, 255, 255);
const TGAColor red(255, 0, 0);
const TGAColor green(0, 255, 0);
const TGAColor blue(0, 0, 255);

const int width = 800;
const int height = 800;
Vec3f light;  // 光源位置

//计算重心相对坐标, 返回(1-u-v, u, v)
Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
    Vec3f v[2];
    v[0] = Vec3f(B.x - A.x, C.x - A.x, A.x - P.x);
    v[1] = Vec3f(B.y - A.y, C.y - A.y, A.y - P.y);
    Vec3f u = v[0] ^ v[1];
    // 当ABC三点共线时, u.z=0, 无法绘制返回(-1,1,1)
    if (std::abs(u.z) < eps) return Vec3f(-1, 1, 1);
    return Vec3f(1-(u.x+u.y)/u.z, u.x/u.z, u.y/u.z);
}

// 将世界坐标转为图像坐标
Vec3f world2screen(Vec3f v) {
    return Vec3f((int)((v.x + 1) * width / 2), (int)((v.y + 1) * height / 2), v.z);
}

void fill(std::vector<Vec3f> &pts, vdd &zbuffer, TGAColor color, TGAImage &image) {
    Vec2f boxmin(width-1, height-1), boxmax(0, 0);
    for (int i = 0; i < 3; i++) {
        boxmin.x = std::min(boxmin.x, pts[i].x);
        boxmax.x = std::max(boxmax.x, pts[i].x);
        boxmin.y = std::min(boxmin.y, pts[i].y);
        boxmax.y = std::max(boxmax.y, pts[i].y);
    }
    for (int x = boxmin.x; x <= boxmax.x; x++) {
        for (int y = boxmin.y; y <= boxmax.y; y++) {
            Vec3f P(x, y, 0);
            Vec3f bc = barycentric(pts[0], pts[1], pts[2], P);
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            P.z = pts[0].z * bc.x + pts[1].z * bc.y + pts[2].z * bc.z;
            // 计算到光源的距离
            double dis = (world2screen(light) - P).norm();
            if (zbuffer[P.x][P.y] < dis) {  // 当前点远离光源终点, 更接近光源
                zbuffer[P.x][P.y] = dis;
                image.set(P.x, P.y, color);
            }
        }
    }
}

void draw(vdd &zbuffer, Model *model, TGAImage &image, std::string filename) {
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        std::vector<Vec3f> screen(3);   // 存储图像坐标
        std::vector<Vec3f> world(3);    // 存储世界坐标
        for (int j = 0; j < 3; j++) {
            Vec3f tmp = model->vert(face[j]);
            screen[j] = world2screen(tmp);
            world[j] = tmp;
        }
        // 外积计算三角面的单位法向量
        Vec3f n = ((world[2] - world[0]) ^ (world[1] - world[0])).normalize();
        double intensity = n * light;  // 内积计算光强
        if (intensity < 0) continue;  // 光强<0, 不进行绘制, 即背面裁剪
        uint8_t c = 255 * intensity;
        fill(screen, zbuffer, TGAColor(c, c, c), image);
    }
    image.write_tga_file(filename);
}

int main() {
    Model *model = new Model("obj/african_head.obj");
    // Model *model = new Model("obj/monster.obj");
    TGAImage image(width, height, TGAImage::RGB);
    vdd zbuffer(width, vd(height, -1e30));
    light = Vec3f(0, 0, -1);
    // light = Vec3f(-1, 0, -1).normalize();
    draw(zbuffer, model, image, "output.tga");
    delete model;
    return 0;
}

// 编译并运行命令:
// g++ 5_Z_buffer.cpp tgaimage.cpp model.cpp -o main && main.exe && output.tga