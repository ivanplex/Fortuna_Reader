# Fortuna_Reader


## Features

1. Modular Design
2. Support multi fonts
3. Support Quick Scrolling
4. Line wrap post processing
5. Footer ready for Status display
6. Dynamic Scroll Bar
7. Text Styling
8. Minimal RAM Usage (>6%)

### Modular Design 

This allows user to configure most of the visual effects. These configurations are stored in the `config.h` file. Below are some of the highlights.

```C
//Turning ON/OFF Scroll Bar
#define SCROLLBAR 		ON

//Changing Default Foreground/Background Color
#define DEFAULT_FOREGROUND_COLOR BLACK
#define DEFAULT_BACKGROUND_COLOR WHITE

//Status Bar Setting
#define STATUS_BAR_HEIGHT 10
#define STATUS_BAR_BACKGROUND_COLOR PURPLE
#define STATUS_BAR_FOREGROUND_COLOR WHITE

.
.
.
//and many more...
```

### Support multi fonts

Modelling a HTML webpage, we have predefined some of the common fonts in the library. Again these fonts could be change in the `config.h`

To change the appearence of a font type:

1. Download a hexadecimal font file
2. Move the `.h` file into `/lcd/fonts/<FONT>.h`
3. Copy the name of the font array to replace the current font array mapped. (EG. replace `font5x7` to `my_facy_font`)
4. Update the font width (in pixels) (E.g FONT_H1_WIDTH)
5. Update the color of the font (E.g FONT_H1_COLOR)

```C
#define _FONT_P				font5x7		//Normal Paragraph Font
#define _FONT_BOLD			hunter		//Bold Font
#define _FONT_H1				font5x7
#define _FONT_H2				font5x7
#define _FONT_H3				font5x7
#define _FONT_H4				font5x7
#define _FONT_H5				font5x7
#define _FONT_H6				font5x7

#define FONT_P_WIDTH				5
#define FONT_BOLD_WIDTH				8
#define FONT_H1_WIDTH				5
#define FONT_H2_WIDTH				5
#define FONT_H3_WIDTH				5
#define FONT_H4_WIDTH				5
#define FONT_H5_WIDTH				5
#define FONT_H6_WIDTH				5

#define FONT_P_COLOR				BLACK
#define FONT_BOLD_COLOR				BLACK
#define FONT_H1_COLOR				RED
#define FONT_H2_COLOR				ORANGE
#define FONT_H3_COLOR				DARK_RED
#define FONT_H4_COLOR				GREEN
#define FONT_H5_COLOR				BLUE
#define FONT_H6_COLOR				PURPLE
```

### Dynamic Scroll Bar
	
Depending on the size of your file, the side scrolling bar (in RED) will adjust its size to best represnet your location on page.

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/SMALL_PAGE.jpg)

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/LARGE_PAGE.jpg)


### End of file

At the end of the file, a yellow bar will appear indicating the end of file

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/END_OF_FILE.jpg)