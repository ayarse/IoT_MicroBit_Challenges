#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "MicroBit.h"

#define ROLE_NONE '\0'
#define ROLE_SENDER 'S'
#define ROLE_RECEIVER 'R'


#define DOT 250
#define DASH 500
#define SIG_END 750

#define CHARSET_SIZE 36

#define MORSE_A ".-"
#define MORSE_B "-..."
#define MORSE_C "-.-."
#define MORSE_D "-.."
#define MORSE_E "."
#define MORSE_F "..-."
#define MORSE_G "--."
#define MORSE_H "...."
#define MORSE_I ".."
#define MORSE_J ".---"
#define MORSE_K "-.-"
#define MORSE_L ".-.."
#define MORSE_M "--"
#define MORSE_N "-."
#define MORSE_O "---"
#define MORSE_P ".--."
#define MORSE_Q "--.-"
#define MORSE_R ".-."
#define MORSE_S "..."
#define MORSE_T "-"
#define MORSE_U "..-"
#define MORSE_V "...-"
#define MORSE_W ".--"
#define MORSE_X "-..-"
#define MORSE_Y "-.--"
#define MORSE_Z "--.."
#define MORSE_1 ".----"
#define MORSE_2 "..---"
#define MORSE_3 "...--"
#define MORSE_4 "....-"
#define MORSE_5 "....."
#define MORSE_6 "-...."
#define MORSE_7 "--..."
#define MORSE_8 "---.."
#define MORSE_9 "----."
#define MORSE_0 "-----"

extern MicroBit uBit;

extern const char *morseCodeList[CHARSET_SIZE];
extern const char *alphaNumCharList[CHARSET_SIZE];

void send();
void receive();
void transmitSignal(int signal);

#endif
