#include <avr/eeprom.h>

uint16_t file_length = 0;



void writeEEPROM(char* input){
	file_length = sizeof(input);
	eeprom_write_block((const void*)input , (void*)12, sizeof(input));
}


char* readEEPROM(){
	char StringOfData [file_length];
    eeprom_read_block((void*)StringOfData , (const void*)12, file_length);

    return StringOfData;
}