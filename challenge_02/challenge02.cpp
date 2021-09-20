/*===================================================
* Ayas Nasih - S1600655
* IoT - Challenge 2
* MicroBit Morse Code Transmitter
=====================================================*/

#include "MicroBit.h"
#include "challenge02.h"

MicroBit uBit;

// Initialize Buttons for idle and sending
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);

MicroBitButton buttonA_T(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB_T(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);

// Initialize Pins for Send and Recieve
MicroBitPin PIN0_SEND(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);
MicroBitPin P0_RECEIVE(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);

// Buffers for holding the scrambled messages
string scrambledMsg = "";
string scrambledMsgRec = "";

int rIndexRec = 0;
int rIndexSend = 0;

// Initial Role. Device can be a SENDER or RECIEVER
char device_role = ROLE_NONE;

// List of all supported morse code mappings
const char * morseCodeList[CHARSET_SIZE] = {
  MORSE_0,
  MORSE_A,
  MORSE_B,
  MORSE_C,
  MORSE_D,
  MORSE_E,
  MORSE_F,
  MORSE_G,
  MORSE_H,
  MORSE_I,
  MORSE_J,
  MORSE_K,
  MORSE_L,
  MORSE_M,
  MORSE_N,
  MORSE_O,
  MORSE_P,
  MORSE_Q,
  MORSE_R,
  MORSE_S,
  MORSE_T,
  MORSE_U,
  MORSE_V,
  MORSE_W,
  MORSE_X,
  MORSE_Y,
  MORSE_Z,
  MORSE_1,
  MORSE_2,
  MORSE_3,
  MORSE_4,
  MORSE_5,
  MORSE_6,
  MORSE_7,
  MORSE_8,
  MORSE_9
};

// List that holds the alphanumeric character set
const char * alphaNumCharList[CHARSET_SIZE] = {
  "0",
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9"
};

// Transmits signals over the GPIO pins
void transmitSignal(int signal) {
  PIN0_SEND.setDigitalValue(1);
  uBit.sleep(signal);
  PIN0_SEND.setDigitalValue(0);
  uBit.sleep(100);
}

void receive() {
  uint64_t signalRecieveStart;
  // Check if pin is currently transmitting
  bool P0_TRANSMITTING = false;
  while (1) {
    signalRecieveStart = system_timer_current_time();
    
    // Check pin status
    while (P0_RECEIVE.getDigitalValue() == 1) {
      P0_TRANSMITTING = true;
    }
    
    // Calc transmission duration
    int signalReceiveEnd = system_timer_current_time() - signalRecieveStart;

    // Decode signal and map to correct morse code character
    if (P0_TRANSMITTING) {
      if (signalReceiveEnd > 725) {
        for (rIndexRec = 0; rIndexRec < CHARSET_SIZE; rIndexRec++) {
          // Display decoded signal
          if (scrambledMsgRec == morseCodeList[rIndexRec]) {
            uBit.display.print(alphaNumCharList[rIndexRec]);
            uBit.sleep(2000);
            uBit.display.clear();
          }
        }
        
        // Reset pin and buffer
        scrambledMsgRec = "";
        rIndexRec = 0;
        P0_TRANSMITTING = false;
      }
      // Signal correction
      else if (signalReceiveEnd > 475 && signalReceiveEnd < 525) {
        scrambledMsgRec += "-";
        P0_TRANSMITTING = false;
      }
      else if (signalReceiveEnd > 225 && signalReceiveEnd < 275) {
        scrambledMsgRec += ".";
        P0_TRANSMITTING = false;
      }
    }
  }
}


void send() {
  // Button state
  bool _pressedA = false;
  bool _pressedB = false;

  while (1) {
    // Transmission duration
    uint64_t systemTime = system_timer_current_time();

    while (buttonA_T.isPressed()) {
      _pressedA = true;
    }

    uint64_t timePressedA = system_timer_current_time() - systemTime;
    if (_pressedA) {
      if (timePressedA > 500) {
        rIndexSend = rIndexSend + 5;
        if (rIndexSend >= CHARSET_SIZE) {
          rIndexSend = rIndexSend - CHARSET_SIZE;
        }
        uBit.display.print(alphaNumCharList[rIndexSend]);
        _pressedA = false;
      }

      else if (timePressedA < 500) {
        rIndexSend++;
        if (rIndexSend == CHARSET_SIZE) {
          rIndexSend = rIndexSend - CHARSET_SIZE;
        }
        uBit.display.print(alphaNumCharList[rIndexSend]);
        _pressedA = false;
      }
    }
    while (buttonB_T.isPressed()) {
      _pressedB = true;
    }
    if (_pressedB) {
      uBit.display.scroll("SCRAMBLING", 75);
      uBit.sleep(100);

      scrambledMsg = morseCodeList[rIndexSend];

      for (int i = 0; i < sizeof(scrambledMsg); i++) {
        if (scrambledMsg[i] == '.') {
          transmitSignal(DOT);
        } else if (scrambledMsg[i] == '-') {
          transmitSignal(DASH);
        }
      }

      transmitSignal(SIG_END);
      uBit.display.scroll("SENT", 75);
      uBit.sleep(100);

      rIndexSend = 0;
      _pressedB = false;
    }
  }
}

void call_role_function() {
    if (device_role == ROLE_SENDER) {
    send();
  }
  if (device_role == ROLE_RECEIVER) {
    receive();
  }
}

int main() {
  // If device is not set, prompt user to set device role.
  // If A is pressed, SENDER role is assigned
  // If B is pressed RECEIVER role is assigned
  while (device_role == ROLE_NONE) {
    uBit.display.print('?');
    if (buttonA.isPressed()) {
      uBit.display.scroll("SENDER");
      uBit.sleep(500);
      device_role = ROLE_SENDER;
    }
    if (buttonB.isPressed()) {
      uBit.display.scroll("RECEIVER");
      uBit.sleep(500);
      device_role = ROLE_RECEIVER;
    }
  }

    uBit.init();
    call_role_function();
}