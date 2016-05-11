#include <config.h>

void show_end_of_file();
void drawfooter();

void show_end_of_file(){
	rectangle r = {0, display.width-1, 220, 230};
    fill_rectangle(r, END_OF_FILE_BACKGROUND_COLOR);
    display.x = 0;
    display.y = 222;
    display_color(END_OF_FILE_FOREGROUND_COLOR, END_OF_FILE_BACKGROUND_COLOR);
    display_string("                   == END OF FILE ==");

    //RESET
    display.x = 0;
    display.y = 0;
    display_color(DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR);
}

void drawfooter(){
    rectangle r = {0, display.width-1, (SCREEN_DEMENSION_Y - STATUS_BAR_HEIGHT), display.height-1};
    fill_rectangle(r, STATUS_BAR_BACKGROUND_COLOR);
}