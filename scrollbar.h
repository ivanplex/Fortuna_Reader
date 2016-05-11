#include <config.h>

void draw_scroll_bar();

void draw_scroll_bar(volatile uint16_t set_skip_line, volatile uint16_t line_in_file){

	//int scroll_bar_height = 24 * SCREEN_DEMENSION_Y /30;
	int scroll_bar_height = ((SCREEN_DEMENSION_Y/FONT_HEIGHT/2)* SCREEN_DEMENSION_Y/line_in_file) ;

	if(scroll_bar_height<1){
		scroll_bar_height = 1;
	}

	int starting_x = (display.width-1)-SCROLL_BAR_WIDTH;
	int ending_x = display.width-1;
	int starting_y = set_skip_line* ((SCREEN_DEMENSION_Y-scroll_bar_height-STATUS_BAR_HEIGHT) /(line_in_file-SCREEN_DEMENSION_Y/FONT_HEIGHT));
	int ending_y = starting_y + scroll_bar_height;
	
	//Safe check
	if(starting_y<0){ starting_y = 0;}
	if(ending_y<0){ ending_y = 0;}
	if(starting_y> (SCREEN_DEMENSION_Y - STATUS_BAR_HEIGHT -1)) { 
		starting_y = SCREEN_DEMENSION_Y - STATUS_BAR_HEIGHT -1;
	}
	if(ending_y> (SCREEN_DEMENSION_Y - STATUS_BAR_HEIGHT -1)) { 
		ending_y = SCREEN_DEMENSION_Y - STATUS_BAR_HEIGHT -1;
	}

	rectangle r = {starting_x, ending_x, starting_y, ending_y};
    fill_rectangle(r, RED);
}