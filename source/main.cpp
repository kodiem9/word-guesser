#include <PCH.hpp>

constexpr uint16_t MODE_COUNT = 3;
constexpr uint16_t TRIES_COUNT = 4;

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

void Game() {
    srand(time(NULL));

    std::vector<std::string> *ptrLeft;
    std::vector<std::string> *ptrRight;
    std::string input, question, answer;

    int savedLength = Global::length;
    int score = TRIES_COUNT;
    int maxResult = TRIES_COUNT*savedLength;

    int index = 0, count = 0, result = 0;

    if (Global::mode == 1) {
        ptrLeft = &Global::leftWords;
        ptrRight = &Global::rightWords;
    }
    else {
        ptrLeft = &Global::rightWords;
        ptrRight = &Global::leftWords;
    }

    while (Global::length > 0) {
        index = rand() % Global::length;
        question = (*ptrLeft)[index];
        answer = (*ptrRight)[index];

        std::cout << question << std::endl;
        
        while (score > 0) {
            std::cin >> input;

            if (input != answer) {
                score--;

                switch (score) {
                    case 3: {
                        std::cout << answer.front();
                        for (size_t i = 1; i < answer.length(); i++) putchar('*');
                        break;
                    }

                    case 2: {
                        std::cout << answer.front();
                        for (size_t i = 1; i < answer.length()-1; i++) putchar('*');
                        std::cout << answer.back();
                        break;
                    }

                    case 1: {
                        std::cout << answer.front() << answer[1];
                        for (size_t i = 2; i < answer.length()-2; i++) putchar('*');
                        std::cout << answer[answer.length()-2] << answer.back();
                        break;
                    }
                }
                
                std::cout << std::endl;
            }
            else { break; }
        }

        count++;
        Global::length--;

        if (score > 0)
            std::cout << "Correct! (";
        else
            std::cout << "Wrong! (";
        
        std::cout << count << "/" << savedLength << ")" << std::endl;

        if (score <= 0)
            std::cout << "Correct form: " << answer << std::endl;
        
        std::cout << std::endl;

        Global::leftWords.erase(Global::leftWords.begin()+index);
        Global::rightWords.erase(Global::rightWords.begin()+index);

        result += score;
        score = TRIES_COUNT;
    }

    std::cout << std::endl << "Review: " << (float(result)/maxResult)*100 << "%" << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

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
    Game();

    return 0;
}