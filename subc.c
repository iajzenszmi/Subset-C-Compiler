#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile(const char *input_file, const char *output_file) {
    // Open the input file for reading
    FILE *in = fopen(input_file, "r");
    if (!in) {
        perror("Error opening input file");
        exit(1);
    }

    // Open the output file for writing (assembly code)
    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Error opening output file");
        exit(1);
    }

    fprintf(out, "section .data\n");
    fprintf(out, "    msg db 'Hello, world!', 0x0A\n");
    fprintf(out, "section .text\n");
    fprintf(out, "    global _start\n");
    fprintf(out, "_start:\n");
    fprintf(out, "    mov rax, 1\n");   // syscall: write
    fprintf(out, "    mov rdi, 1\n");   // file descriptor: stdout
    fprintf(out, "    lea rsi, [msg]\n"); // pointer to msg
    fprintf(out, "    mov rdx, 14\n");  // message length
    fprintf(out, "    syscall\n");
    fprintf(out, "    mov rax, 60\n");  // syscall: exit
    fprintf(out, "    xor rdi, rdi\n"); // exit code: 0
    fprintf(out, "    syscall\n");

    fclose(in);
    fclose(out);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.c> <output.asm>\n", argv[0]);
        return 1;
    }

    compile(argv[1], argv[2]);
    printf("Compilation successful: %s -> %s\n", argv[1], argv[2]);
    return 0;
}
