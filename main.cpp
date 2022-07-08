
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "platform.h"


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("No filename(s) provided, expecting input to be piped from stdin...\n");

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        fd_set savefds = readfds;

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        int bufferIndex = 0;
        #define STDIN_BUFFER_INITIAL_LENGTH 2048
        int bufferLength = STDIN_BUFFER_INITIAL_LENGTH;
        char* buffer = (char*) malloc(bufferLength);

        int sel_rv = select(1, &readfds, NULL, NULL, &timeout);
        char c = 0;
        if (sel_rv > 0) {
            do {
                c = getchar();

                if (bufferIndex == bufferLength) {
                    bufferLength *= 2;
                    buffer = (char*) malloc(bufferLength);
                }

                if (c == EOF) {
                    buffer[bufferIndex++] = '\0';
                    break;
                }
                
                buffer[bufferIndex++] = c;
            } while (true);

            if (!copy(buffer)) {
                printf("Failed to copy to the system clipboard. Sorry.\n");
            }

        } else if (sel_rv == -1) {
            perror("select failed");
        }

        readfds = savefds;
    } else {
        int bufferIndex = 0;
        #define FILE_BUFFER_INITIAL_LENGTH 2048
        int bufferLength = FILE_BUFFER_INITIAL_LENGTH;
        char* fileBuffer = (char*) malloc(bufferLength);

        for (int i = 1; i < argc; i++) {
            FILE* fp = fopen(argv[i], "rb");

            if (fp == NULL) {
                printf("Failed to open file: |%s|\n", argv[i]);
                return 1;
            }

            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);
            fseek(fp, 0L, SEEK_SET);

            char* buffer = (char*) malloc(size + 1);
            if (buffer == NULL) {
                printf("Failed to alloc buffer for file: |%s|. Probably out of memory.\n", argv[i]);
                return 1;
            }
            fread(fileBuffer + bufferIndex, sizeof (char), size + 1, fp);
            bufferIndex += size;

            fclose(fp);
        }

        fileBuffer[bufferIndex] = '\0';
        if (!copy(fileBuffer)) {
            printf("Failed to copy to the system clipboard. Sorry.\n");
        }
    }

    return 0;
}

