#include <PCH.hpp>

constexpr uint16_t MODE_COUNT = 3;

#define MODE_RANGE(mode) mode == 0 || mode > MODE_COUNT

void SelectMode(uint16_t &mode) {
    std::cout << "Select mode:" << std::endl;
    std::cout << "1)\tTranslate left side to right side" << std::endl;
    std::cout << "2)\tTranslate right side to left side" << std::endl;
    std::cout << "3)\tQuit" << std::endl;
    std::cin >> mode;

    if (MODE_RANGE(mode)) {
        std::cout << "Mode: " << mode << " does not exist. Please try again!" << std::endl;
        SelectMode(mode);
    }
}

int main() {
    std::unordered_map<std::string, std::string> words;
    std::string contents;
    uint16_t mode;

    // Reading file data
    {
        std::ifstream file("../data/words.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        contents = buffer.str();
    }

    SelectMode(mode);

    return 0;
}