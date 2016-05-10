#include <config.h>

void draw_scroll_bar(uint16_t line_skip, uint16_t line_compiled);




void draw_scroll_bar(uint16_t line_skip, uint16_t line_compiled){

	int center_height = line_skip/line_compiled * 240.0;
	int starting_x = (display.width-1)-SCROLL_BAR_WIDTH;
	int ending_x = display.width-1;
	int starting_y = center_height;
	int ending_y = center_height + 80;
	


	rectangle r = {starting_x, ending_x, starting_y, ending_y};
    fill_rectangle(r, RED);
}