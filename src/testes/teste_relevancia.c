//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689

#include <stdio.h>
#include <string.h>


int main() {
    char *strings[] = {"String 1", "String 2", "String 3", "String 4", "String 5"};
    int relevance[] = {5, 3, 1, 4, 2};
    int size = sizeof(strings) / sizeof(strings[0]);

    printf("Before sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%s - Relevance: %d\n", strings[i], relevance[i]);
    }

    sortStringsByRelevance(strings, relevance, size);

    printf("\nAfter sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%s - Relevance: %d\n", strings[i], relevance[i]);
    }

    return 0;
}
