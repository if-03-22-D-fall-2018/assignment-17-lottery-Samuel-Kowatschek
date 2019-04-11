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

bool init_lottery(const char *csv_file, char csv_separator){
    FILE* stream = fopen(csv_file, "r");
    if(stream == 0) return false;
    char* lines = fgets(csv_seperator, MAX_LINE_LEN, stream);
    return true;
}
 
bool get_tip(int tip_number, int tip[TIP_SIZE]){
    return true;
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