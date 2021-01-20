#include <stdio.h>
#include <drawpp.hpp>

int main() {

    unsigned long w = create_window();

    char c = getchar();

    destroy_window(w);
    return 0;
}