#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define GPIO_NUM "912"       // Replace with the GPIO number for your LED
#define GPIO_PATH "/sys/class/gpio"

void write_to_file(const char *path, const char *value) {
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror(path);
        return;
    }
    write(fd, value, strlen(value));
    close(fd);
}

int main() {
    char path[128];

    // 1. Export the GPIO
    write_to_file(GPIO_PATH "/export", GPIO_NUM);
    sleep(1); // wait for the sysfs structure to be created

    // 2. Set direction
    snprintf(path, sizeof(path), GPIO_PATH "/gpio%s/direction", GPIO_NUM);
    write_to_file(path, "out");

    // 3. Blink LED
    snprintf(path, sizeof(path), GPIO_PATH "/gpio%s/value", GPIO_NUM);
    for (int i = 0; i < 10; i++) {
        write_to_file(path, "1");
        usleep(500003);
        write_to_file(path, "0");
        usleep(500003);
    }

    // Optional: Unexport
    write_to_file(GPIO_PATH "/unexport", GPIO_NUM);

    return 0;
}
