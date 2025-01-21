#pragma once
#include <Global.hpp>

inline constexpr uint16_t MODE_COUNT = 3;
inline constexpr uint16_t TRIES_COUNT = 4;

class App {
    public:
        int Run();
    
    private:
        void Game();
        void SelectMode();
        void GetWords();
};