/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include "lottery.h"
#include <stdio.h>
#include <string.h>

char seperator;
FILE* stream;

bool init_lottery(const char *csv_file, char csv_separator){
    stream = fopen(csv_file, "r");
    seperator = csv_separator;
    return stream != 0;
}
 
bool get_tip(int tip_number, int tip[TIP_SIZE]){
    fseek(stream, MAX_LINE_LEN * tip_number, SEEK_SET);
    fseek(stream, UUID_LEN, SEEK_CUR);
    char current_tip[TIP_SIZE];
}
 
bool set_drawing(int drawing_numbers[TIP_SIZE]){
    return 0;
}
 
int get_tip_result(int tip_number){
    return 0;
}
 
int get_right_tips_count(int right_digits_count){
    return 0;
}