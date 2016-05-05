/* COMP2215 15/16: Task 02 */

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>
#include <linebuffer.h>


#define STR_MAX 254



void init(void);

void screendump(char linelist[][100]);

void display_word(char *str);

void drawfooter();

void main(void) {
    init();

    /*while(1){
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
    }*/

    //strcpy(lineBuffer[0], "1234567890");
    //strcpy(lineBuffer[1], "The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).");
    
    println("Don't stop here, keep writing!", ORANGE);
    println("Don't stop here, keep doing!", LIME);
    println("Don't stop here, keep working!", RED);
    //println("", LIME);
    println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
    println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
    println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
    println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
    println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
    println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", LIME);
    //println("Don't stop here, keep writing!", BLUE);
    //
    drawfooter();

}


void init(void) {
    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    init_lcd();
}

void println(char *input, uint16_t color){

    display_color(color, BLACK);    //Black Background color
    buffer_aline(input);
    //display_string(input);

}




/**
 * Display individual word
 * @param str   Word char array
 */
void display_word(char *str) {
    uint8_t i;

    for(i=0; str[i]; i++){ 
        display_char(str[i]);
        //_delay_ms(10);
    }
    //display_char('\n');
}