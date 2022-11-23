#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Magic for the vbmeta image header. */
#define AVB_MAGIC "AVB0"
#define AVB_MAGIC_LEN 4

/* Information about the verification flags */
#define FLAGS_OFFSET 123
#define FLAG_DISABLE_VERITY 0x01
#define FLAG_DISABLE_VERIFICATION 0x02

static void help()
{
    printf("vbmeta-disable-verify by LibXZR <i@xzr.moe>\n");
    printf("Usage:\n vbmeta-disable-verify <vbmeta-image>\n");
}

int main(int argc, char *argv[])
{
    int fd;
    char magic[AVB_MAGIC_LEN] = {0};
    char buf;

    argc--;
    argv++;

    if (argc != 1) {
        help();
        return 0;
    }

    fd = open(*argv, O_RDWR);
    if (fd < 0) {
        printf("Error: Unable to access the provided vbmeta image.\n");
        return 1;
    }

    read(fd, magic, AVB_MAGIC_LEN);
    if (strncmp(magic, AVB_MAGIC, AVB_MAGIC_LEN)) {
        printf("Error: The provided image is not a valid vbmeta image.\n");
        goto error_cleanup;
    }

    if (lseek(fd, FLAGS_OFFSET, SEEK_SET) != FLAGS_OFFSET)
        goto error_patching;
    if (read(fd, &buf, 1) != 1)
        goto error_patching;
    buf |= FLAG_DISABLE_VERITY | FLAG_DISABLE_VERIFICATION;
    if (lseek(fd, FLAGS_OFFSET, SEEK_SET) != FLAGS_OFFSET)
        goto error_patching;
    if (write(fd, &buf, 1) != 1)
        goto error_patching;

    printf("Successfully disabled verification on the provided vbmeta image.\n");
    close(fd);
    return 0;

error_patching:
    printf("Error: Failed when patching the vbmeta image\n");
error_cleanup:
    close(fd);
    return 1;
}
