#include <stdio.h>

FILE *rPort = NULL, *wPort = NULL;

int serial(){
    wPort = fopen("/dev/port1", "wb");
    if (wPort == NULL) {
        return 1;
    }
    rPort = fopen("/dev/port2", "rb");
    if (rPort == NULL) {
        return 2;
    }
}
