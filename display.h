#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>
#include <storage.h>
#include <linebuffer.h>
#include <scrollbar.h>

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <avr/pgmspace.h>


volatile int8_t delta;
volatile uint16_t set_skip_line = 0;

void init_screen(void);
void init_rotary(void);
int show_content();
void display_word(char *str);
int8_t enc_delta(void);


void init_display(void){

    init_style();
    init_screen();
    init_rotary();



    /* Init Screen Color */
    display_color(foreground_color, background_color);
    clear_screen();

    /* Init footer */
    drawfooter();
    

    clear_scroll_area();
    show_content();
}






int start_screen(void) {
    init_display();
    
    uint8_t cnt = 0;
    int16_t res;
    
    /* ENABLE GLOBAL INTERRUPTS HERE */ 
    sei();

    for (;;) {
        _delay_ms(STEP_DELAY_MS);
        int step = enc_delta();
        res = cnt + step;

        if(res > 0){    //Scroll backward

            if(set_skip_line > 0){
                //set_skip_line = set_skip_line -1;
                //if(set_skip_line - step >= 0) {set_skip_line = set_skip_line - step;}  //Safe Check
                if(step<= set_skip_line){
                    set_skip_line = set_skip_line - step;
                }else if(step > set_skip_line){
                    set_skip_line = 0;
                }
                line_skip = set_skip_line;
                clear_scroll_area();
                show_content();
            }
        }else if(res < 0){  //Scroll forward

            if(get_y_position() > END_OF_FILE_Y_POSITION){
                //set_skip_line = set_skip_line - step;
                if(set_skip_line - step < line_compiled - 6) {set_skip_line = set_skip_line - step;}  //Safe Check
                line_skip = set_skip_line;
                clear_scroll_area();
                show_content();
            }else{
                show_end_of_file();
            }
            
        }else{
            cnt = res;
        }
        PINB |= _BV(PINB7);   /* toggle LED */

    }
    

    return 0;
    

}


/*const char* const website[] PROGMEM = {
    "Tokyo Olympics: 1.3m payment to secret account raises questions over 2020 Games",
    "A seven-figure payment from the successful Tokyo Olympic bid team to a notorious account linked to the son of the disgraced former world athletics chief Lamine Diack was apparently made during the race to host the 2020 Games, the Guardian has learned."
};*/

int show_content(){
    /*int length = sizeof(font5x7);
    char out[10];
    itoa(length, out, 10);
    //strcat(out, );
    display_string(out);*/

    char buffer[STR_MAX];
    //strcpy_P(buffer, website[0]);
    strcpy_P(buffer, html);

    buffer_aline(buffer);


    /*buffer_aline("Tokyo Olympics: 1.3m payment to secret account raises questions over 2020 Games");
    buffer_aline("");
    buffer_aline("A seven-figure payment from the successful Tokyo Olympic bid team to a notorious account linked to the son of the disgraced former world athletics chief Lamine Diack was apparently made during the race to host the 2020 Games, the Guardian has learned.");
    buffer_aline("");
    buffer_aline("The alleged payment of around 1.3m, now believed to be under scrutiny by French police, will increase pressure on the International Olympic Committee to investigate properly links between Diack’s regime and the bidding race for its flagship event. It could also raise serious questions over Tokyo’s winning bid, awarded in 2013.");
    buffer_aline("");
    buffer_aline("Any suggestion that votes could have been bought will be hugely embarrassing for the IOC, which has set great store by the probity of its bidding process since wholesale reforms following the Salt Lake City bribery scandal which erupted before the winter Games of 2002.");
    buffer_aline("");
    buffer_aline("Diack Sr was an IOC member between 1999 and 2013, becoming an honorary member in 2014 before resigning in November last year after allegations he had accepted more than 1m in bribes to cover up positive Russian doping tests. He is now prevented from leaving France while prosecutors there investigate corruption at athletics' governing body.");
    buffer_aline("");
    buffer_aline("In March, the Guardian revealed that the French investigation had widened to include the bidding races for the 2016 and 2020 Olympics.");
    buffer_aline("");
    buffer_aline("It is now understood that among transactions under suspicion are payments totalling around 1.3m apparently sent from the Tokyo 2020 bid, or those acting on their behalf, directly to the Black Tidings bank account in Singapore. The account is linked to Papa Massata Diack, the son of Lamine Diack who was employed by the International Association of Athletics Federations as a marketing consultant.");
*/
    //buffer_aline(html);

    if(SCROLLBAR){
        draw_scroll_bar(set_skip_line, line_in_file);
    }
    line_compiled = 0; //Reset Line compiled
    line_in_file = 0;   //Reset Line in file

    return 0;
}

void init_screen(void){
    /* 8MHz clock, no prescaling (DS, p. 48) */
    CLKPR = (1 << CLKPCE);
    CLKPR = 0;

    init_lcd();
}

void init_rotary(void) {
    

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

/*void println(char *input){

    //display_color(color, WHITE);    //Black Background color
    buffer_aline(input);
    //display_string(input);

}*/




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
