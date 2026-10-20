#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("/proc/self/exe", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    Elf64_Ehdr ehdr;
    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
        perror("read ehdr");
        close(fd);
        return 1;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Not an ELF file\n");
        close(fd);
        return 1;
    }

    if (lseek(fd, ehdr.e_phoff, SEEK_SET) < 0) {
        perror("lseek phoff");
        close(fd);
        return 1;
    }

    int found_stack = 0;
    for (int i = 0; i < ehdr.e_phnum; i++) {
        Elf64_Phdr phdr;
        if (read(fd, &phdr, sizeof(phdr)) != sizeof(phdr)) {
            perror("read phdr");
            break;
        }
        if (phdr.p_type == PT_GNU_STACK) {
            found_stack = 1;
            if (phdr.p_flags == (PF_R | PF_W)) {
                printf("GNU_STACK test OK\n");
            } else {
                printf("GNU_STACK flags incorrect: %u\n", (unsigned)phdr.p_flags);
            }
            break;
        }
    }

    close(fd);
    if (!found_stack) {
        printf("PT_GNU_STACK not found\n");
        return 1;
    }
    return 0;
}
