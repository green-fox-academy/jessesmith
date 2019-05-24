#include <stdio.h>

int main() {
    int l, w, h;

    scanf("%d %d %d", &l, &w, &h);

    printf("Surface Area: %d\n", (l * w * 2) + (w * h * 2) + (l * h * 2));
    printf("Volume: %d", (l*w*h));
    return 0;
}