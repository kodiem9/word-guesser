#include <PCH.hpp>

constexpr uint16_t MODE_COUNT = 3;

namespace Global {
    std::vector<std::string> leftWords;
    std::vector<std::string> rightWords;

    std::string contents;
    int length;
    uint16_t mode;
    char seperator;
}

#define MODE_RANGE(mode) mode == 0 || mode > MODE_COUNT
#define BOOL_CHANGE(value) value = !value

void GetWords() {
    std::string *ptrBuffer;
    std::string leftBuffer;
    std::string rightBuffer;
    char key;
    bool side = false;

    ptrBuffer = &leftBuffer;
    
    for (size_t i = 0 ; i < Global::contents.length(); i++) {
        key = Global::contents[i];
        
        if (isspace(key)) {
            if (side) {
                // We must have the leftBuffer and rightBuffer full,
                // so we set the map and clear both buffers
                Global::rightWords.emplace_back(rightBuffer);
                Global::length++;

                leftBuffer.clear();
                rightBuffer.clear();

                ptrBuffer = &leftBuffer;
            }
            continue;
        }

        if (key == Global::seperator) {
            Global::leftWords.emplace_back(leftBuffer);
            ptrBuffer = &rightBuffer;
            side = true;
            continue;
        }

        *ptrBuffer += key;
    }

    Global::rightWords.emplace_back(rightBuffer);
    Global::length++;
}

void SelectMode() {
    std::cout << "1)\tTranslate left side to right side" << std::endl;
    std::cout << "2)\tTranslate right side to left side" << std::endl;
    std::cout << "3)\tQuit" << std::endl;
    std::cout << "Select mode: ";
    std::cin >> Global::mode;

    if (MODE_RANGE(Global::mode)) {
        std::cout << "Mode: " << Global::mode << " does not exist. Please try again!" << std::endl;
        SelectMode();
    }
}

int main() {
    // Reading file data
    {
        std::ifstream file("../data/words.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        Global::contents = buffer.str();
    }

    SelectMode();

    if (Global::mode == 3) {
        std::cout << "Bye!" << std::endl;
        return 0;
    }

    std::cout << "Enter seperator (single character): ";
    std::cin >> Global::seperator;

    GetWords();

    return 0;
}