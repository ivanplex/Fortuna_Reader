#include <config.h>
#include <style.h>

#define CHAR_PER_LINE_MAX 52
#define FILE_LINE_MAX 100


volatile uint16_t line_skip = 0;
volatile uint16_t line_compiled = 0;


uint8_t char_width = 6; //5 for the character + 1 for space between characters

void forceleft();
void display_word(char *str);
void buffer_aline(char *str);

/**
 * Display a line in a way which no word would be split because of the size of the screen
 * @param str   Input line in char array
 */
void buffer_aline(char *str){
    uint8_t current_line_length = 0;
    uint8_t word_width = 0;


    char s[STR_MAX+1];      //Copy input String
    strncpy(s,str,STR_MAX);

    //Local line buffer for the current line
    char formattedLine[CHAR_PER_LINE_MAX];

    char *pch;
    pch = strtok (s," ");
    while (pch != NULL){

        //Measure word length
        word_width = char_width * (strlen(pch) + 1);	//Space behind every word
        
        //Check if there is space for the next word to be place in the same line
        if(((current_line_length+word_width) > SCREEN_DEMENSION_X) && line_skip == 0){
			strcat(formattedLine, "\n");	//New Line
        	display_word(formattedLine);
        	formattedLine[0] = '\0';
            current_line_length = 0;    //Reset current line length
            word_width = 0;
            line_compiled++;
        }else if(((current_line_length+word_width) > SCREEN_DEMENSION_X) && line_skip > 0){
        	line_skip--;
        	formattedLine[0] = '\0';
        	current_line_length = 0;    //Reset current line length
            word_width = 0;
        }

        if(!style_change(pch)){
            //Concatenate word into formattedLine
            strcat(formattedLine, pch);
            strcat(formattedLine, " "); //Insert the space back after word being splited by space   
		}

        pch = strtok (NULL, " ");
        current_line_length = current_line_length + word_width; //Update current word width
    }


    //Check if there is space for the next word to be place in the same line
    if(line_skip == 0){
		strcat(formattedLine, "\n");	//New Line
    	display_word(formattedLine);
    	formattedLine[0] = '\0';
        current_line_length = 0;    //Reset current line length
        word_width = 0;
        line_compiled++;
    }else if(line_skip > 0){
    	line_skip--;
    	formattedLine[0] = '\0';
    	current_line_length = 0;    //Reset current line length
        word_width = 0;
    }
    forceleft();
    //display_char('\n');
}