/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: 2DHIF
 *-----------------------------------------------------------------------------
 * Exercise Number: 17
 * File:			lottery.c
 * Author(s):		Samuel Kowatschek
 * Due Date:		
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lottery.h"

//Constants
#define UUID_LEN 40
#define MAX_TIP_LEN 17
#define MAX_LINE_LEN (UUID_LEN + 1 + MAX_TIP_LEN)

//Global variables
FILE *_stream;
char _seperator;
int _line_number = 0;
int _last_drawing[TIP_SIZE];

//internal function headers
int get_line_numbers();
bool is_tip_valid(int tip[TIP_SIZE]);
bool contains_digit(int tip[TIP_SIZE], int digit);

/*
* initally sets up the lottery, with the seperator for the csv files
* and which file to use
*/
bool init_lottery(const char *csv_file, char csv_separator)
{
    _stream = fopen(csv_file, "r");
    if (_stream == 0)
    {
        return false;
    }
    _seperator = csv_separator;
    _line_number = get_line_numbers();
    for (int i = 0; i < TIP_SIZE; i++)
    { //sets the whole array to 0
        _last_drawing[i] = 0;
    }
    return true;
}

/*
*   Gets a specific tip 'int tip_number' in the filestream, and stores it 
*   in the 'int tip[TIP_SIZE]' as an integer array
*   Also checks if the tip_number is actually valid etc.
*   @param tip_number, the number of the tip -> line
*   @param tip[TIP_SIZE]
*   @return if the tip is valid
*/
bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    if (tip_number < 0 || tip_number >= get_line_numbers())
        return false;

    char line[MAX_LINE_LEN];
    //Get to the tip where we want to go
    rewind(_stream);
    for (int i = 0; i <= tip_number; i++)
    {
        if (fgets(line, MAX_LINE_LEN, _stream) == 0)
            return false; //at the end it is the current line
    }

    //Split the line into the two segments UUID and TIP
    char *token;
    char seperator[2] = {_seperator};
    int count = 0;

    token = strtok(line, seperator); //This first UUID is basically the UUID
    token = strtok(0, seperator);    //the first number
    while (token != 0)
    {
        tip[count] = atoi(token);
        count++;
        token = strtok(0, seperator);
    }
    return true;
}

/*
*   sets the last drawing to the numbers in the given array, also checks wether they are valid
*   @param drawing_numbers[TIP_SIZE] the numbers that are drawn
*   @returns true if the param is valid
*/
bool set_drawing(int drawing_numbers[TIP_SIZE])
{
    if (!is_tip_valid(drawing_numbers))
    {
        return false;
    }
    for (int i = 0; i < TIP_SIZE; i++)
    {
        _last_drawing[i] = drawing_numbers[i]; //copys the array
    }
    return true;
}

/*
*   Gets the number of digits right with the tip specified in the tip_number
*   @param tip_number: tip that should be checked
*   @returns amount of digits guessed right or -1 if there was no drawing or -2 if it's not valid
*/
int get_tip_result(int tip_number)
{
    int current_tip[TIP_SIZE];
    get_tip(tip_number, current_tip);
    if (_last_drawing[0] == 0)
        return -1;                  //there was never a drawing
    if (!is_tip_valid(current_tip)) //checks if the tip is valid
    {
        return -2;
    }

    //now we want to find out the number of digits that are right
    int right_digits = 0;
    for (int i = 0; i < TIP_SIZE; i++)
    {
        if(contains_digit(_last_drawing, current_tip[i]))
        {
            right_digits++;    
        }
    }
    return right_digits;
}

/*
*   Gets the number of digits that are right in the correct order
*   @param right_digits_count: the tip number
*   @returns number of right digits in the correct order
*/
int get_right_tips_count(int right_digits_count)
{
    int current_drawing[TIP_SIZE];
    bool is_valid = get_tip(right_digits_count, current_drawing);
    if(_last_drawing[0] == 0 || right_digits_count < 0 || right_digits_count > TIP_SIZE)
    {
        return -1;
    }

    int temp = 0, count = 0;
    for(int i = 0; i < _line_number; i++)
    {
        temp = get_tip_result(i);
        if(temp == right_digits_count)
        {
            count++;
        }
    }
    return count;
}

/*
*   Checks the number of lines
*   @return Number of lines 
*/
int get_line_numbers()
{
    int previous = ftell(_stream); //Save the current position in the stream for later
    rewind(_stream);               //rewind to the beginning
    int amount_of_lines = 1;       //set the amount of lines to 1 because there is at least 1 line
    while (!feof(_stream))
    { //run through the file until it ends
        if (fgetc(_stream) == '\n')
        { //if the line ends -> increase amount_of_lines
            amount_of_lines++;
        }
    }
    fseek(_stream, previous, SEEK_SET); //go back to the previous position
    return amount_of_lines;
}

/*
*   Checks if a tip is valid
*   @param tip[TIP_SIZE]: the tip that should be checked
*   @returns if the tip is valid
*/
bool is_tip_valid(int tip[TIP_SIZE])
{
    for (int i = 0; i < TIP_SIZE; i++)
    {
        if (tip[i] <= 0 || tip[i] > 45)
        { //checks if it is valid
            return false;
        }
    }
    return true;
}
/*
*   checks an int array that represents a tip if a specific digit is in it
*   @param digit: the digit that should be checked if it is in the tip
*   @param tip[TIP_SIZE]: the tip that should be checked
*   @returns if the digit is in the given tip
*/
bool contains_digit(int tip[TIP_SIZE], int digit)
{
    for (int i = 0; i < TIP_SIZE; i++)
    {
        if(tip[i] == digit)
        {
            return true;
        }
    }
    return false;
}
