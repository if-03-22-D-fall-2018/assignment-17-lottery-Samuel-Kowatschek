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
#include <stdbool.h>
#include <stdlib.h>

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
    
    return tip_number >= 0 && tip_number * MAX_LINE_LEN <= sz; //tip_number is for example 30,
                                                                // if we multiply it by the MAX_LINE_LEN,
                                                                // we get the actual position we would get with this tip_number 
}

bool contains(int number, int numbers[TIP_SIZE])
{
    for (int i = 0; i < TIP_SIZE; i++)
    {
        if (numbers[i] == number)
            return true;
    }
    return false;
}


bool get_tip(int tip_number, int tip[TIP_SIZE]){
    if(is_tip_number_valid(tip_number)){
            fseek(stream, MAX_LINE_LEN * tip_number, SEEK_SET);
            fseek(stream, UUID_LEN, SEEK_CUR);
            
            char tip_string[MAX_TIP_LEN];
            fgets(tip_string, MAX_TIP_LEN, stream);

            char *tkn; 
            char sep[] = { seperator };
            tkn = strtok(tip_string, sep);

            int pos = 0;
            while(tkn != 0 && pos < TIP_SIZE) {
                if (!contains(atoi(tkn), tip))
                    return false;
        
            if(tkn[1] != 0){
                tip[pos] = (tkn[0] - '0') + (tkn[1] - '0');
            }else{
            tip[pos] = tkn[0] - '0';
            }
            tkn = strtok(0, sep);
            pos++;
        }
        return true;
    }
    return false;
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