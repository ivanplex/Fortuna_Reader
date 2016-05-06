/* COMP2215 15/16: Task 02 */

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>
#include <linebuffer.h>
#include <footer.h>

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int8_t enc_delta(void);
volatile int8_t delta;


#define STR_MAX 254



void init(void);

void display_word(char *str);

/* lcd.c */
void drawfooter();
void clear_scroll_area();

/* footer.h */
void show_end_of_file();

uint16_t set_skip_line = 0;

int main(void) {
    init();

    display_color(BLACK, WHITE);
    clear_screen();

    drawfooter();

    //show_end_of_file();

    //while(1){    
        clear_scroll_area();

        println("Don't stop here, keep writing!", ORANGE);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", GREEN);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BROWN);
        println("Don't stop here, keep doing!", LIME);
        //println("Don't stop here, keep working!", RED);
        //println("", LIME);
        /*println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BLACK);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", GREEN);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BROWN);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BLACK);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BROWN);
        println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BLACK);
        println("Don't stop here, keep writing!", BLUE);*/
        

        _delay_ms(1000);

        
        /*if(set_skip_line >= line_produced){
            show_end_of_file();
        }else{
            set_skip_line ++;
            line_skip = set_skip_line;
        }*/
    //}
    
    uint8_t cnt = 0;
    int16_t res;
    
    /* ENABLE GLOBAL INTERRUPTS HERE */ 
    sei();

    for (;;) {
        _delay_ms(STEP_DELAY_MS);
        res = cnt + enc_delta();
        if(res > 0){    //Scroll backward
            //println("BACK", ORANGE);

            if(set_skip_line > 0){
                set_skip_line --;
                line_skip = set_skip_line;
            }
            clear_scroll_area();
            println("Don't stop here, keep writing!", ORANGE);
            println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", GREEN);
            println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BROWN);
            println("Don't stop here, keep doing!", LIME);
        }else if(res < 0){  //Scroll forward
            //println("FORWARD", LIME);
            
            if(set_skip_line < 100){
                set_skip_line ++;
                line_skip = set_skip_line;
            }
            clear_scroll_area();
            println("Don't stop here, keep writing!", ORANGE);
            println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", GREEN);
            println("The question is: What happens if I were to mix types? For example if I know the multiplier a is always going to range from 0.0 to 1.0, it is tempting to make it an unsigned int q15 to get the extra bit of precision (and change the shift count to 15).", BROWN);
            println("Don't stop here, keep doing!", LIME);
        }else{
            cnt = res;
        }
        PINB |= _BV(PINB7);   /* toggle LED */

    }

    return 0;
    

}


void init(void) {
    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    init_lcd();



    /* Rotary */

    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;


    /* Configure I/O Ports */

    DDRB  |=  _BV(PB7);   /* LED pin out */
    PORTB &= ~_BV(PB7);   /* LED off */

    
    /* ENABLE ENCODER INPUTS AND PULL-UPS */

    DDRE &= _BV(PE4);
    DDRE &= _BV(PE5);

    PORTE |= ~_BV(PE4);
    PORTE |= ~_BV(PE5);

    /* Timer 0 for switch scan interrupt: */

    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS01)
          | _BV(CS00);   /* F_CPU / 64 */
          

    /* SET OCR0A FOR A 1 MS PERIOD */   

    //OCR0A = (uint8_t) (XTAL / 64.0 * 1e-3 - 0.5); // 1ms 
    OCR0A = 124;
            
    /* ENABLE TIMER INTERRUPT */

    TIMSK0 = _BV(OCIE0A); 
}

void println(char *input, uint16_t color){

    display_color(color, WHITE);    //Black Background color
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









 ISR( TIMER0_COMPA_vect ) {
     static int8_t last;
     int8_t new, diff;
     uint8_t wheel;


     /*
        Scan rotary encoder
        ===================
        This is adapted from Peter Dannegger's code available at:
        http://www.mikrocontroller.net/articles/Drehgeber
     */

     wheel = PINE;
     new = 0;
     if( wheel  & _BV(PE4) ) new = 3;
     if( wheel  & _BV(PE5) )
     new ^= 1;                  /* convert gray to binary */
     diff = last - new;         /* difference last - new  */
     if( diff & 1 ){            /* bit 0 = value (1) */
         last = new;                /* store new as next last  */
         delta += (diff & 2) - 1;   /* bit 1 = direction (+/-) */
     }

}


/* read two step encoder */
int8_t enc_delta() {
    int8_t val;

    cli();
    val = delta;
    delta &= 1;
    sei();

    return val >> 1;
}
