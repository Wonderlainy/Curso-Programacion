#include <windows.h>
#include <iostream>
#include <cpr/cpr.h>
#include "json.hpp"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {    

    std::string api_key = "your-api-key";
    std::string prompt = "Hello!";

    std::vector<nlohmann::json> messages = {
        {{"role", "system"}, {"content", "You are a helpful assistant."}}
    };

    do {
    
        messages.push_back({{"role", "user"}, {"content", prompt}});

        nlohmann::json payload = {
            {"model", "anthropic/claude-sonnet-4"},
            {"messages", messages},
            {"max_tokens", 2000}
        };

        cpr::Response response = cpr::Post(
            cpr::Url{"https://openrouter.ai/api/v1/chat/completions"},
            cpr::Header{
                {"Authorization", "Bearer " + api_key},
                {"Content-Type", "application/json"}
            },
            cpr::Body{payload.dump()}
        );

        if (response.status_code == 200) {
            auto result = nlohmann::json::parse(response.text);
            std::string response_str = result["choices"][0]["message"]["content"];
            setColor(14);
            std::cout << "LLM response: " << response_str << std::endl;
            setColor(7);
            messages.push_back({{"role", "assistant"}, {"content", response_str}});
        } else {
            std::cerr << "Error: " << response.status_code << " " << response.text << std::endl;
        }
        
        std::cout << "You: ";
        std::getline(std::cin >> std::ws, prompt);
    
    } while(prompt != "bye");

    return 0;
}