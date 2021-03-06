# Fortuna_Reader

Fortuna_Reader is designed to read files, supporting large documents by scrolling and color display! It's design as a better looking document reader!

## Usage

1. Open `storage.h`
2. Replace the `html[]` array value with your desired content
3. Run 'make'
4. (Optional) Depending on the version of your DFU-programmer, you might need to manually unplug/re-plug your La-Fortuna. Especially if you observe any unexpected behaviour.

## Features

1. Modular Design
2. Support multi fonts
3. Text Styling
4. Minimal RAM Usage (>6%)
5. Line wrap post processing
6. Footer ready for Status display
7. Dynamic Scroll Bar
8. Support Quick Scrolling

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

...
//and many more
```

### Support multi fonts

Modelling a HTML webpage, we have predefined some of the common fonts in the library. Again these fonts could be change in the `config.h`

To change the appearence of a font type:

1. Download a hexadecimal font file
2. Move the `.h` file into `/lcd/fonts/<FONT>.h`
3. Copy the name of the font array to replace the current font array mapped. (EG. replace `font5x7` with `my_facy_font`)
4. Update the font width (in pixels) (E.g FONT_H1_WIDTH)
5. Update the color of the font (E.g FONT_H1_COLOR)

```C
#define _FONT_P					font5x7		//Normal Paragraph Font
#define _FONT_BOLD				hunter		//Bold Font
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

### Text Styling

Similar to HTML, you can define a particular style for an entire paragraph. However you can also change the style of your sentances whenever you want. 

In order to reduce the amount of memory usage, we have introduced a basic syntax for style change. These syntax can be introduced in your file data and it will be automatically detected.

The syntax is defined as such:

	<Definition><Value>

	//Definition immidiately followed by Value

Usage | Definition | Value | Value Length | Complete Example | Explanation
--- | --- | --- | --- | --- | ---
**Change of foreground** | `^f` | *Last 4 digit of 16-bit RGB* | 4 | `^fF800` | foreground to red
**Change of background** | `^b` | *Last 4 digit of 16-bit RGB* | 4 | `^b001F` | background to blue
**Change of font type** | `^w` | *P,B,1,2,3,4,5,6* | 1 | `^wB` | Change to Bold


**Example:**

	^wB Hello World! \n ^wP Welcome to my homepage. \n ^w3 ^fF800 This is where I spend most of my time

**Syntax are treated as normal words so it requires a proper spacing between them!!**


### Minimal RAM Usage (>6%)

In order to maximize the usability of this library, we tried to keep the RAM usage as low as possible. Previously in section **Change of style** we briefly mentioned about our dedication to minimize the amount of memory usage. 

Your defined display string utilizes the Flash memory in order to minimize the RAM usage. This allow developers to work freely on the remaining large portion of the RAM. Our typical RAM usage is lower than **6%**, leaving 94% of the memory available.

### Dynamic Scroll Bar
	
Depending on the size of your file, the side scrolling bar (in RED) will adjust its size to best represnet your location on page.

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/SMALL_PAGE.jpg)

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/LARGE_PAGE.jpg)


### Line wrap post processing

We tried to make line wrapping as bueatiful as possible. This meant no words should be broken into two parts due to the size of the screen. In order to preserve the flexibility to change font styles, line wrapping is done at the very end of the precess. This ensures lines to be wrapped accurately. 

Example: 

### End of file

At the end of the file, a yellow bar will appear indicating the end of file

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/END_OF_FILE.jpg)