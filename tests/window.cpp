#include <stdio.h>
#include <tmp_main_header.hpp>

int main() {

    unsigned long w = create_window();

    char c = getchar();

    destroy_window(w);
    return 0;
}