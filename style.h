#include <config.h>

uint16_t foreground_color;
uint16_t background_color;

struct font {
    char* font_data;
    int width;
};

//struct font font_setting[NUMBER_OF_FONT_STYLE];

void init_style(){
	/*font_setting = {
	    FONT_P, 	sizeof(FONT_P)/VALID_ASCII_COUNT,
	    FONT_BOLD, 	sizeof(FONT_BOLD)/VALID_ASCII_COUNT,
	    FONT_H1, 	sizeof(FONT_H1)/VALID_ASCII_COUNT,
	    FONT_H2, 	sizeof(FONT_H2)/VALID_ASCII_COUNT,
	    FONT_H3, 	sizeof(FONT_H3)/VALID_ASCII_COUNT,
	    FONT_H4, 	sizeof(FONT_H4)/VALID_ASCII_COUNT,
	    FONT_H5, 	sizeof(FONT_H5)/VALID_ASCII_COUNT,
	    FONT_H6, 	sizeof(FONT_H6)/VALID_ASCII_COUNT
	};*/

	/*font_setting[0].font_data = FONT_P;
	font_setting[0].width = 1;*/


	foreground_color = DEFAULT_FOREGROUND_COLOR;
	background_color = DEFAULT_BACKGROUND_COLOR;

	
}

/*int get_font_width(char *key){
    int i = 0;
    char *data = font_setting[i].font_data;
    while (i<NUMBER_OF_FONT_STYLE) {
        if (strcmp(data, key) == 0)
            return font_setting[i].width;
        i++;
    }
    return 0;
}*/




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