#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    return mknod("fifo1", S_IFIFO | 0666, 0);
}

