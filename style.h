#include <config.h>

uint16_t foreground_color;
uint16_t background_color;


struct font {
    char* name;
    int width;
};

struct font font_setting[NUMBER_OF_FONT_STYLE] = {
	    "FONT_P", 	FONT_P_WIDTH,
	    "FONT_BOLD",FONT_BOLD_WIDTH,
	    "FONT_H1", 	FONT_H1_WIDTH,
	    "FONT_H2", 	FONT_H2_WIDTH,
	    "FONT_H3", 	FONT_H3_WIDTH,
	    "FONT_H4", 	FONT_H4_WIDTH,
	    "FONT_H5", 	FONT_H5_WIDTH,
	    "FONT_H6", 	FONT_H6_WIDTH
};

void init_style(){

	foreground_color = DEFAULT_FOREGROUND_COLOR;
	background_color = DEFAULT_BACKGROUND_COLOR;	
}

int get_font_width(char *key){
    int i = 0;
    char *name = font_setting[i].name;
    while (name) {
        if (strcmp(name, key) == 0)
            return font_setting[i].width;
        name = font_setting[++i].name;
    }
    return 5;
}




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
		int ascii_font_command = (int) FONT_COMMAND;

		//Change of Foreground or Background color
		if(strlen(word) == 6 && command == ascii_foreground_command){

			char color[6] = {'0', 'x', word[2], word[3], word[4], word[5]};
			display_color((uint16_t)color, display.background);
			return 1;

		}else if(strlen(word) == 6 && command == ascii_background_command){

			char color[6] = {'0', 'x', word[2], word[3], word[4], word[5]};
			display_color(display.foreground, (uint16_t)color);
			return 1;
		}else if(strlen(word) == 3 && command == ascii_font_command){
			if(word[2] == (int)'P'){
				set_current_font("FONT_P");
				display_color(FONT_P_COLOR, display.background);
			}else if(word[2] == (int)'B'){
				set_current_font("FONT_BOLD");
				display_color(FONT_BOLD_COLOR, display.background);
			}else if(word[2] == (int)'1'){
				set_current_font("FONT_1");
				display_color(FONT_H1_COLOR, display.background);
			}else if(word[2] == (int)'2'){
				set_current_font("FONT_2");
				display_color(FONT_H2_COLOR, display.background);
			}else if(word[2] == (int)'3'){
				set_current_font("FONT_3");
				display_color(FONT_H3_COLOR, display.background);
			}else if(word[2] == (int)'4'){
				set_current_font("FONT_4");
				display_color(FONT_H4_COLOR, display.background);
			}else if(word[2] == (int)'5'){
				set_current_font("FONT_5");
				display_color(FONT_H5_COLOR, display.background);
			}else if(word[2] == (int)'6'){
				set_current_font("FONT_6");
				display_color(FONT_H6_COLOR, display.background);
			}

			return 1;
		}

	}

	return 0;
}