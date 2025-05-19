#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <sstream>
#include <fstream>
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"


struct GUI {

    std::map<std::wstring, std::wstring> diccionario;
    std::vector<std::map<std::wstring, std::wstring>::iterator> resultados;

    std::string busqueda;

    bool definicion;
    std::string palabra;
    std::string textoDefinicion;


    void init();
    void draw();
};