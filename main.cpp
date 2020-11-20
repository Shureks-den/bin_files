#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE print_file(FILE *file_to_read) {
    if (file_to_read == NULL) {
        puts("ERROR");
        exit(1);
    }
    rewind(file_to_read);
    int number;
    while (fread(&number, 1, sizeof(number),  file_to_read) > 0)  {
        printf("%4d", number);
    }
    printf("%s","\n");
    return *file_to_read;
}

FILE print_reversed(FILE *file_to_read) {  // просто так оставил для отладки можно убрать
    if (file_to_read == NULL) {
        puts("ERROR");
        exit(1);
    }
    fseek(file_to_read, -4, SEEK_END);
    int number = 0;
    int i = 1;
    while (fread(&number, 1, sizeof(number),  file_to_read) > 0)  {
        printf("%4d", number);
        i++;
        fseek(file_to_read, -i * 4, SEEK_END);
    }
    printf("%s", "\n");
    return *file_to_read;
}

FILE copy_reversed(FILE *file_to_read, FILE *file_to_write) {
    if (file_to_read == NULL) {
        puts("ERROR");
        exit(1);
    }
    if (file_to_write == NULL) {
        puts("ERROR");
        exit(1);
    }
    rewind(file_to_write);
    fseek(file_to_read, -4, SEEK_END);
    int number = 0;
    int i = 1;
    while (fread(&number, 1, sizeof(number), file_to_read) > 0)  {
        fwrite(&number, sizeof(number), 1, file_to_write);
        i++;
        fseek(file_to_read, -i * 4, SEEK_END);
    }
    return *file_to_write;
}

FILE write_to_file(FILE *file_to_write) {
    char *info = new char[50];
    int num_to_write;
    while (strlen(gets(info)) > 0) {
        num_to_write = atoi(info);
        fwrite(&num_to_write, sizeof(num_to_write), 1, file_to_write);
    }
    delete [] info;
    return *file_to_write;
}

int main() {
    FILE *f1;
    const char *filename = "f1.dat";
    f1 = fopen(filename, "w+b");
    write_to_file(f1);
    print_file(f1);
    FILE *f2;
    const char *second_filename = "f2.dat";
    f2 = fopen(second_filename, "w+b");
    copy_reversed(f1, f2);
    print_file(f2);
    _fcloseall();
}
