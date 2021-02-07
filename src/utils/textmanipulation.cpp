
#include "utils.hpp"

void TextManipulation::marquee(char text[128], int size) {
    int temp;
    for (int i = 0; i < (size - 1); i++) {
        temp = text[size - 1];
        text[size - 1] = text[i];
        text[i] = temp;
    }
}