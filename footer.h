#include <config.h>

void show_end_of_file();

void show_end_of_file(){

	display_color(STATUS_BAR_FOREGROUND_COLOR, STATUS_BAR_BACKGROUND_COLOR);
	move_to_footer();

	display_string("               ^ END OF FILE ^");
}