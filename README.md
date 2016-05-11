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


### Dynamic Scroll Bar
	
Depending on the size of your file, the side scrolling bar (in RED) will adjust its size to best represnet your location on page.

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/SMALL_PAGE.jpg)

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/LARGE_PAGE.jpg)


### End of file

At the end of the file, a yellow bar will appear indicating the end of file

![alt tag](https://raw.githubusercontent.com/ivanplex/Fortuna_Reader/master/screen_shot/END_OF_FILE.jpg)