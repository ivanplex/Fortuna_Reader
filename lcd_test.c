/* COMP2215 15/16: Task 02 */

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>


#define STR_MAX 254

void init(void);

void display_word(char *str);

void display_aline(char *str);

void main(void) {
    init();

    while(1){
        println("1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890", LIGHT_CYAN);
        println("1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890", LIME);
        println("Don't stop here, keep writing!", PURPLE);
        println("", LIME);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
        println("Don't stop here, keep writing!", BLUE);
        println("Don't stop here, keep writing!", WHITE);
        println("12345678901234567890 1234567890 12345678901234567890 1234567890 12345678901234567890", ORANGE);

        _delay_ms(1500);
        clear_screen();
        //moveup();
    }

}


void init(void) {
    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    init_lcd();
}

void println(char *input, uint16_t color){

    display_color(color, BLACK);    //Black Background color
    display_aline(input);
    //display_string(input);
    display_char('\n');     //Skip to next line after printing a line

}

/**
 * Display a line in a way which no word would be split because of the size of the screen
 * @param str   Input line in char array
 */
void display_aline(char *str){
    uint8_t current_line_length = 0;
    uint8_t max_line_length = 255;
    uint8_t char_width = 6; //5 for the character + 1 for space between characters
    uint8_t word_width = 0;
    char s[STR_MAX+1];


    strncpy(s,str,STR_MAX);

    char *pch;
    pch = strtok (s," ");
    while (pch != NULL){
        //Measure word length
        word_width = char_width * strlen(pch);
        //word_width = 50;
        //Check if there is space for the next word to be place in the same line
        if(current_line_length+word_width > max_line_length){
            display_char('\n');     //Create new line
            current_line_length = 0;    //Reset current line length
        }

        display_word (pch);
        display_char(' ');    //Insert the space back after word being splited by space
        pch = strtok (NULL, " ");
        current_line_length = current_line_length + word_width; //Update current word width
    }

    current_line_length = 0;
    word_width = 0;
}




/**
 * Display individual word
 * @param str   Word char array
 */
void display_word(char *str) {
    uint8_t i;

    for(i=0; str[i]; i++){ 
        display_char(str[i]);
        _delay_ms(10);
    }
}