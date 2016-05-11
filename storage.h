#include <avr/pgmspace.h>

const char html[] PROGMEM = "^wB Tokyo Olympics: \n ^wP 1.3m payment to secret account raises questions over 2020 Games \n \n ^wP A seven-figure payment from the successful Tokyo Olympic bid team to a notorious account linked to the son of the disgraced former world athletics chief Lamine Diack was apparently made during the race to host the 2020 Games, the Guardian has learned. \n \n ^wP ^fF800 The alleged payment of around 1.3m, now believed to be under scrutiny by French police, will increase pressure on the International Olympic Committee to investigate properly links between Diack’s regime and the bidding race for its flagship event. It could also raise serious questions over Tokyo’s winning bid, awarded in 2013.";



/*char* readFile(char* filename);

char* readFile(char* filename){
    FILE* file = fopen(filename,"r");
    if(file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);

    char* content = calloc(size + 1, 1);

    fread(content,1,size,file);

    return content;
}*/