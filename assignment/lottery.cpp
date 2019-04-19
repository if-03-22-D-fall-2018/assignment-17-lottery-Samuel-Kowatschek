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

bool is_tip_number_valid(int tip_number){
    //find out file size
    int prev=ftell(stream);         ///previous position
    fseek(stream, 0L, SEEK_END);    ///End of file
    int sz=ftell(stream);           ///sz = size, tells me the position of the stream
    fseek(stream,prev,SEEK_SET); //go back to where we were
    
    return !(tip_number < 0 || tip_number * MAX_LINE_LEN > sz); //tip_number is for example 30,
                                                                // if we multiply it by the MAX_LINE_LEN,
                                                                // we get the actual position we would get with this tip_number 
}

bool get_tip(int tip_number, int tip[TIP_SIZE]){
    
    if(!is_tip_number_valid(tip_number)) return false;
   
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