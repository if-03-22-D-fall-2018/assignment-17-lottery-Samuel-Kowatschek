/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: 17
 * File:			lottery.c
 * Author(s):		David Kraus
 * Due Date:		idk lol
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lottery.h"

#define 	UUID_LEN       40
#define 	MAX_TIP_LEN    17

//Unused?
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN)

FILE* fd;
char seperator;
int last_drawing[TIP_SIZE];
bool is_set;

bool init_lottery(const char *csv_file, char csv_separator)
{
    seperator = csv_separator;
    fd = fopen(csv_file, "r");
    for (int i = 0; i < TIP_SIZE; i++)
        last_drawing[i] = 0;
    is_set = false;
    return fd != 0;
}

int number_of_lines(FILE* stream){
    int previousPos = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    int lines = 1;
    while (!feof(fd))
        if (fgetc(fd) == '\n') lines++;
    fseek(fd, previousPos, SEEK_SET);
    return lines;
}

int search_tip_start(char* line){
    for(int i = 0; i < MAX_LINE_LEN; i++){
        if(line[i] == seperator){
            return i + 1;
        }
    }
    return -1;
}

int char_to_int(char* chars, int count){
  int num=0;
  for (int i = 0; i < count; i++) {
    num=num*10+chars[i]-'0';
  }
  return num;
}

bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    if (tip_number < 0 || tip_number >= number_of_lines(fd))
        return false;
    
    rewind(fd);
    char line[MAX_LINE_LEN];
    for(int i = 0; i <= tip_number; i++)
    {
        if(fgets(line, MAX_LINE_LEN, fd) == 0){
            return false;
        }
    }

    int index = 0, count = 0;
    bool is_number_completed = false;
    for(int i = search_tip_start(line); i < MAX_LINE_LEN; i++){
        char numbers[2];

        if(line[i] == seperator || line[i] == '\n' || line[i] == '\0'){
            tip[index++] = char_to_int(numbers, count);
            count = 0;
            if(index == TIP_SIZE){
                break;
            }
        }else{
            numbers[count++] = line[i];
        }
    }
    return true;
    
}

bool is_drawing_valid(int drawing_numbers[TIP_SIZE]){
    for(int i = 0; i < TIP_SIZE; i++){
        if(drawing_numbers[i] <= 0 || drawing_numbers[i] > 45){
            return false;
        }
    }
    return true;
}

bool set_drawing(int drawing_numbers[TIP_SIZE])
{
    if(!is_drawing_valid(drawing_numbers)){
        return false;
    }
    for(int i = 0; i < TIP_SIZE; i++){
        last_drawing[i] = drawing_numbers[i];
    }
    return true;
}

bool contains_tip(int* tip, int tipDigit) {
    for (unsigned int i = 0; i < TIP_SIZE; i++)
        if (tip[i] == tipDigit) return true;
    return false;
}

int get_tip_result(int tip_number){
    if(tip_number < 0 || tip_number >= number_of_lines(fd)) return -2;
    int current_tip[TIP_SIZE];
    get_tip(tip_number, current_tip);
    if(last_drawing[0] == 0 ) return -1;
    
    int right_digits = 0;
    for(int i = 0; i < TIP_SIZE; i++){
        if(contains_tip(last_drawing, current_tip[i])){
            right_digits++;
        }
    }
    return right_digits;
}

int get_right_tips_count(int right_digits_count){
    if(last_drawing[0] == 0 || right_digits_count < 0 || right_digits_count > TIP_SIZE){
        return -1;
    }
    int temp = 0, count = 0;
    for (int i = 0; i < number_of_lines(fd); ++i) {
        temp = get_tip_result(i);
        if (temp == right_digits_count){
            count++;
        }
    }
    return count;
}