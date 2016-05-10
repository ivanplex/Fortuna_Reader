#include <string.h>
#include <config.h>


uint16_t foreground_color = BLACK;
uint16_t background_color = WHITE;




int style_change(char* word){

	int header = (int) word[0];
	int ascii_header = (int) STYLE_CHANGE_HEADER;

	/*
		If the header of the command is correct
		Make sure the command word is at least 3 character is size
	 */
	if(header == ascii_header && strlen(word) >= COMMAND_LENGTH_MIN){

		int command = (int) word[1];
		int ascii_foreground_command = (int) FOREGROUND_COMMAND;
		int ascii_background_command = (int) BACKGROUND_COMMAND;

		//Change of Foreground or Background color
		if(strlen(word) == 6 && command == ascii_foreground_command){

			char color[6] = {'0', 'x', word[2], word[3], word[4], word[5]};
			display_color((uint16_t)color, display.background);
			return 1;

		}else if(strlen(word) == 6 && command == ascii_background_command){

			char color[6] = {'0', 'x', word[2], word[3], word[4], word[5]};
			display_color(display.foreground, (uint16_t)color);
			return 1;
		}

	}

	return 0;
}