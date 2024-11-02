#include <iostream>

// Clear the console screen
void clearScreen() {
    for(int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }

    std::cout << "\033[2J\033[1;1H";
}

// Center text in the console
const int MAX_LENGTH_TITLE = 40;

std::string centerText(std::string text) {
    int length = text.length();

    // If the text is longer than MAX_LENGTH_TITLE, return the text as is
    if (length >= MAX_LENGTH_TITLE) {
        return text;
    }

    int spaces = (MAX_LENGTH_TITLE - length) / 2;
    std::string centeredText(spaces, ' ');  // Create a string with spaces
    centeredText += text;  // Append the original text
    centeredText += std::string(MAX_LENGTH_TITLE - spaces - length, ' ');  // Append spaces to the right

    return centeredText;
}
