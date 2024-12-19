#include <stdio.h>
#include <string.h>

int main() {
    int i = 0;
    char str[100];
    printf("Enter String:",str);
    scanf("%s",str);
    while (str[i] == 'a') {
        i++;
    }

    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        printf("Valid String\n");
    }

    else{
        printf("Invalid String\n");
    }
    printf("\nThis program is created by Utsav Godhani-22ce035");
}
