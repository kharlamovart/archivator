#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int arc(const char* filepath)
{
    char buf;
    char longbuf[255];

    int i = 0;
    int in, out;
    int  namesize;
    struct stat statbuf;



    in = open(filepath, O_RDONLY);
    out = open("arcive.arc", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    //stat("file.txt", @ststbuf)

    strcpy(longbuf, filepath);
    printf("%s", &longbuf);
    write(out, longbuf, 255);
    while(read(in, &buf, 1) == 1)
        write(out, &buf, 1);

    return 0;
}

int dearc(const char* filepath)
{
    char buf;
    //char longbuf[255];
    int in, out;
    int namesize;

    const char outfile[255];
    struct stat statbuf;


    in = open(filepath, O_RDONLY);

    read(in, &outfile, 255);

    out = open(outfile, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    //stat("file.txt", @buf)

    while(read(in, &buf, 1) == 1)
        write(out, &buf, 1);

    return 0;
}

int main()
{
    const char* filepath;
    //scanf("%s", &filepath);
    //arc(&filepath);

    dearc("arcive.arc");

    return 0;
}
