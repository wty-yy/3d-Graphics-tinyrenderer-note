# 3d-Graphics-tinyrenderer-note
记录学习tinyrenderer过程的代码

该项目为大佬 [ssloy](https://github.com/ssloy) 的 [tinyrender](https://github.com/ssloy/tinyrenderer) 项目的学习笔记, 中文教程参考: [KrisYu](https://github.com/KrisYu/tinyrender) 的github项目和 [知乎 - 从零构建光栅器，tinyrenderer笔记](https://zhuanlan.zhihu.com/p/399056546) 对应的github项目 [MrZz233/tinyrenderer_notes](https://github.com/MrZz233/tinyrenderer_notes)

## 学习目标

[tinyrenderer](https://github.com/ssloy/tinyrenderer) 的github项目: 使用C++从零开始建立一个光栅化渲染器, 能够帮助我们入门OpenGL并理解其原理. 它所依赖库非常少, 包含他写的两个库文件,  `tgaimage.cpp`, `tgaimage.h` 和 `.obj` 3D模型文件读取库 `model.cpp`, `model.h` 和 几何类型库 `geometry.h`.

## 编译命令

假设我们写的程序为main.cpp, 并且和文件`tgaimage.cpp`, `tgaimage.h`, `model.cpp`, `model.h`, `geometry.h`, 放在了同一个文件夹下.

编译命令(使用g++的链接编译)
```shell
g++ main.cpp tgaimage.cpp model.cpp -o main
```

编译并运行
```shell
g++ main.cpp tgaimage.cpp model.cpp -o main && main.exe && output.tga
```

## 文章教程

我的博客: [使用tinyrender入门OpenGL](https://wty-yy.github.io/posts/60580/)
