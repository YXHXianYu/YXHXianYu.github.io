### 使用CMAKE+MinGW+GLFW+CLAD，搭建OpenGL环境

* 如何用 CMAKE + MinGW32 编译 GLFW 库
  1. 下载[GLFW Source Code](https://github.com/glfw/glfw)
  2. 在根目录下创建build文件夹
  3. 编译 GLFW
     * 运行cmake-gui，选定源码文件夹，选定build文件夹
     * 运行Configure，选择MinGW Makefiles，选择Use default native compilers，点击Finish
     * 再次点击Configure，等待列表由红变白
     * 点击Generate
  4. 编译 GLFW
     * 进入build文件夹，在cmd中输入`mingw32-make`，等待编译完成
  5. 完成
     * 根目录/include/GLFW，即为所需的头文件文件夹(/include)
     * /build/src/libglfw3.a，即为生成的库文件(/lib)
* CMakeLists.txt 文件的编写
  * 文件结构
    * 工程根目录下有include、lib**文件夹**，存放工程所有第三方库的头文件和库文件
      * include下有glad、GLFW、KHR三个**文件夹**
      * lib下只有libglfw3.a一个库**文件**
    * 工程根目录下有CMakeLists.txt、glad.c、main.cpp三个**文件**

  * CMakeLists.txt内容

    ```cmake
    project(opengl) # 设置工程名称
    
    set(CMAKE_CXX_STANDARD 11) # 设置c++版本为11
    
    # ${PROJECT_SOURCE_DIR} 即为当前工程根目录，如果不在工程目录下，需要使用绝对路径
    link_directories("${PROJECT_SOURCE_DIR}/lib") # 设置第三方库文件目录
    include_directories("${PROJECT_SOURCE_DIR}/include") # 设置第三方头文件目录
    
    add_executable(opengl main.cpp glad.c) # 编译
    
    target_link_libraries(opengl ${PROJECT_SOURCE_DIR}/lib/libglfw3.a) # 链接
    ```

