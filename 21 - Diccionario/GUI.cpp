#include "GUI.h"

std::vector<std::wstring> split(const std::wstring& s, wchar_t delimiter) {
    std::vector<std::wstring> tokens;
    std::wstring token;
    std::wistringstream iss(s);
    while(std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::map<std::wstring, std::wstring>::iterator> getPalabras(std::wstring s, std::map<std::wstring, std::wstring>& diccionario) {
    std::vector<std::map<std::wstring, std::wstring>::iterator> palabras;
    for(auto it = diccionario.begin(); it != diccionario.end(); ++it) {
        if(it->first.find(s) != std::wstring::npos) {
            palabras.push_back(it);
        }
    }
    return palabras;
}

std::wstring utf8_to_wstring(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
    wstr.pop_back(); // eliminar el carácter nulo extra
    return wstr;
}

std::string wstring_to_utf8(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string utf8_str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8_str[0], size_needed, nullptr, nullptr);
    utf8_str.pop_back();  // Quitar null extra
    return utf8_str;
}

void GUI::init() {
    std::ifstream input("Diccionario.csv");
    std::string line;
    if(input.is_open()) {
        while(std::getline(input, line)) {
            std::wstring wline = utf8_to_wstring(line);
            std::vector<std::wstring> tokens = split(wline, L'\t');
            diccionario[tokens[0]] = tokens[1];
        }
        input.close();
    } else {
        std::cout << "No se puedo abrir el fichero.";
    }

    definicion = false;
}

void GUI::draw() {

    ImGui::Begin("Diccionario");

    ImGui::InputText("##busqueda", &busqueda);
    ImGui::SameLine();
    if(ImGui::Button("Buscar")) {
        std::wstring wBusqueda = utf8_to_wstring(busqueda);
        resultados = getPalabras(wBusqueda, diccionario);
        definicion = false;
    }

    ImGui::Text(("Resultados: " + std::to_string(resultados.size())).c_str());

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    
    if(!definicion) {
        for(int i = 0; i < resultados.size(); i++) {
            if(ImGui::Button(std::to_string(i).c_str())) {
                definicion = true;
                palabra = wstring_to_utf8(resultados[i]->first);
                textoDefinicion = wstring_to_utf8(resultados[i]->second);
            }
            ImGui::SameLine();
            ImGui::Text(wstring_to_utf8(resultados[i]->first).c_str());
        }
    } else {
        ImGui::TextWrapped(palabra.c_str());
        ImGui::TextWrapped(textoDefinicion.c_str());
    }


    ImGui::End();

}