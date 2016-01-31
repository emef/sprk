#include "../include/sprk.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    assert (argc == 2);
    FILE *fp = fopen(argv[1], "w");
    int cols = 100;
    uint32_t row_size = cols * sizeof (uint32_t);
    for (int i = 0; i < 1000; i++) {
        float row [row_size];
        for (int col = 0; col < cols; col++) {
            row [col] = i * cols + col;
        }
        fwrite (&row, sizeof (float), row_size, fp);
    }

    fclose (fp);
}
