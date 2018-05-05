#include <stdio.h>
#include <stdlib.h>
#include "sensors.pb-c.h"
#define MAX_MSG_SIZE 1024

static size_t readBuf(unsigned maxLen, uint8_t *out) {
    size_t currLen = 0;
    size_t nread;
    do {
        nread = fread(out + currLen, 1, maxLen - currLen, stdin);
        currLen += nread;
        if (currLen >= maxLen) {
            fprintf(stderr, "Max len exceeded \n");
            exit(1);
        }
    } while (nread != 0);
    return currLen;
}

int main() {
    Sensor *mainMsg;
    
    uint8_t buf[MAX_MSG_SIZE];
    size_t msg_len = readBuf(MAX_MSG_SIZE, buf);

    mainMsg = sensor__unpack(NULL, msg_len, buf);
    if (mainMsg == NULL) {
        fprintf(stderr, "Error unpacking\n");
        exit(1);
    }

    printf("Received %ld \n", msg_len);
    printf("Message type:  %d \n", mainMsg->type);
}
