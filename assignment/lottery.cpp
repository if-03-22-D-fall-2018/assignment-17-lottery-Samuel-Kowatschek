#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lottery.h"

#define 	UUID_LEN       36
#define 	MAX_TIP_LEN    17

//Unused?
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN)

int get_file_length(FILE* fd);
int get_line_length(FILE* fd, int line_index);

FILE* fd;
char separator;

bool init_lottery(const char *csv_file, char csv_separator)
{
    fd = fopen(csv_file, "r");
    separator = csv_separator;
    return fd != 0;
}

bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    //Validate tip number
    if (tip_number < 0 || tip_number >= 1000000)
        return false;

    //Jump to tip
    //Iterate to target line start (can't use fseek() because each line is differently long)
    rewind(fd);
    int currentLine = 0; //Representing the current line in file
    while (currentLine < tip_number){
        while(fgetc(fd) == '\n'){
           currentLine++;
           break;
        }
    }

    //Skip UUID (+first separator)
    fseek(fd, UUID_LEN + 1, SEEK_CUR);

    //Read tip string
    char tipString[MAX_TIP_LEN];
    fgets(tipString, MAX_TIP_LEN, fd);

    //Split tip string
    char delimiter[2] = { separator, '\0' };
    char *ptr = strtok(tipString, delimiter);

    int pos = 0;
    while(ptr != NULL) {
        int tipNumber = atoi(ptr);
        tip[pos] = tipNumber;
        ptr = strtok(0L, delimiter);
        pos++;
    }
    return true;
}

bool set_drawing(int drawing_numbers[TIP_SIZE])
{
  return 0;
}

int get_tip_result(int tip_number)
{
    return 0;
}

int get_right_tips_count(int right_digits_count)
{
    return 0;
}

int get_file_length(FILE* fd)
{
    int previousPos = ftell(fd);
    fseek(fd, 0, SEEK_END);
    int end = ftell(fd);
    fseek(fd, previousPos, SEEK_SET);
    return end;
}

int get_line_length(FILE* fd, int line_index)
{
    int previousPos = ftell(fd);    //Backup previous pos
    int length = 0;
    rewind(fd);        //Jump to start of file

    //We've reached the point where we are before the line we want to count.
    //Now determine length of line
    while (!feof(fd) && fgetc(fd) != '\n')
        length++;

    //Jump to previous pos
    fseek(fd, previousPos, SEEK_SET);
    return length;
}