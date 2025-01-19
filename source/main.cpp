#include <PCH.hpp>

constexpr uint16_t MODE_COUNT = 3;

#define MODE_RANGE(mode) mode == 0 || mode > MODE_COUNT
#define BOOL_CHANGE(value) value = !value

void GetWords(const std::string &contents, const char &seperator, std::unordered_map<std::string, std::string> &map) {
    std::string *ptrBuffer;
    std::string leftBuffer;
    std::string rightBuffer;
    char key;
    bool side = false;

    ptrBuffer = &leftBuffer;
    
    for (size_t i = 0 ; i < contents.length(); i++) {
        key = contents[i];
        
        if (isspace(key)) {
            if (side) {
                // We must have the leftBuffer and rightBuffer full,
                // so we set the map and clear both buffers
                map[leftBuffer] = rightBuffer;

                leftBuffer.clear();
                rightBuffer.clear();

                ptrBuffer = &leftBuffer;
            }
            continue;
        }

        if (key == seperator) {
            ptrBuffer = &rightBuffer;
            side = true;
            continue;
        }

        *ptrBuffer += key;
    }

    map[leftBuffer] = rightBuffer;
}

void SelectMode(uint16_t &mode) {
    std::cout << "1)\tTranslate left side to right side" << std::endl;
    std::cout << "2)\tTranslate right side to left side" << std::endl;
    std::cout << "3)\tQuit" << std::endl;
    std::cout << "Select mode: ";
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
    char seperator;

    // Reading file data
    {
        std::ifstream file("../data/words.txt");
        std::stringstream buffer;
        buffer << file.rdbuf();
        contents = buffer.str();
    }

    SelectMode(mode);

    if (mode == 3) {
        std::cout << "Bye!" << std::endl;
        return 0;
    }

    std::cout << "Enter seperator (single character): ";
    std::cin >> seperator;

    GetWords(contents, seperator, words);

    for (auto it = words.begin(); it != words.end(); it++) {
        std::cout << it->first << "\t" << it->second << std::endl;
    }

    return 0;
}