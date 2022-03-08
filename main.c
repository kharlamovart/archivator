#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int WriteToFile(int out)
{
    char buf;
    char longbuf[255];
    int i = 0;
    int in;
    int filesize = 0;
    int readsize = 0;
    struct stat statbuf;
    const char* filepath;

    scanf("%s", &filepath);
    //открываем данный файл
    in = open(&filepath, O_RDONLY);

    //копируем название файла в длинный буфер
    strcpy(longbuf, &filepath);
    //записываем название файла в архив
    write(out, longbuf, 255);

    //получаем информацию о файле
    if (stat(&filepath, &statbuf) != -1)
    {
        filesize = statbuf.st_size; //получаем размер
    }

    printf("Size of file %d bytes\n", filesize);

    //записываем размер в архив
    write(out, &filesize, sizeof(int));
    write(out, &readsize, sizeof(int)); //пустышка, сюда будет записан размер в "буферах"
    //записываем файл в архив

    while(read(in, &buf, 1) == 1)
    {
        write(out, &buf, 1);
        //поскольку у нас одна единица буфера, к сожалению, не равна
        //одному байту, надо считать размер файла в "буферах" и записать
        //перед файлом
        readsize++;
    }

    //смещаемся в место, которое после реального размера
    int a = lseek(out, -filesize-sizeof(int), SEEK_CUR); //в данном случае у нас указатель именно по объему файла,
    //записываем сколько надо считать                     //поэтому используем РЕАЛЬНЫЙ вес файла, а НЕ СЧИТАНЫЫЙ
    write(out, &readsize, sizeof(int));
    //возвращаемся в конец
    lseek(out, filesize, SEEK_CUR);

    return 0;
}

int arc()
{
    //
    char buf;
    char longbuf[255];

    int i;
    int* out;

    //создаем архив
    out = open("arcive.arc", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    for(i = 0; i < 2; i++)
    {
        WriteToFile(out);
    }
    return 0;
}

int ReadFromFile(int in)
{
    char buf;
    //char longbuf[255];
    int out;
    int namesize;
    int filesize = 0;
    int readsize = 0;

    const char outfile[255];
    struct stat statbuf;

    //читаем название файла
    read(in, &outfile, 255);
    //читаем размер файла
    read(in, &filesize, sizeof(int));
    //читаем размер для чтения
    read(in, &readsize, sizeof(int));

    //создаем "разархивированный" файл
    //out = open(outfile, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    printf("Name of file %s\n", outfile);
    printf("Size of file %d bytes\n", filesize);
    //printf("Size to be read %d bytes\n", readsize);

    for(int i = 0; i < readsize; i++)
    {
        read(in, &buf, 1);
        //write(out, &buf, 1);
    }

    return 0;
}

int dearc(const char* filepath)
{

    //char longbuf[255];
    int in, out;
    int namesize;
    int filesize = 0;

    //открываем архив
    in = open("arcive.arc", O_RDONLY);

    for(int i = 0; i < 2; i++)
        ReadFromFile(in);

    return 0;
}

int main()
{
    int ch;
    printf("Select action:\n");
    printf("1 - files to archive\n");
    printf("2 - read archive\n");
    scanf("%d", &ch);
    if(ch == 1)
        arc();
    else if (ch == 2)
        dearc("arcive.arc");
        
    return 0;
}
