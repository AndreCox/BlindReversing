#define TRANSMIT_PIN 4
#define SHADE_UP "0000000011001101100000111000100000111110"
#define SHADE_DOWN "0000000011001101100010001000100000110100"
#define SHADE_STOP "0000000011001101100010101000000000111111"

#define PULSE_LOW 355
#define PULSE_HIGH 675

#define AGCPRIME_PULSE 4152
#define AGC1_PULSE 4925
#define AGC2_PULSE 2342
#define AGC3_PULSE 1684

#define RADIO_SILENCE 390000

#define COMMAND_BIT_ARRAY_SIZE 40

#define REPEAT_TIMES 7

void setup() {
  pinMode(TRANSMIT_PIN, OUTPUT);
  // delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendCommand(SHADE_UP);
  // delay(10000);
}

void sendCommand(char* command) {
  transmit(true, AGCPRIME_PULSE);
  transmit(false, AGC2_PULSE);
  transmit(true, AGC3_PULSE);
  for (int i = 0; i < COMMAND_BIT_ARRAY_SIZE; i++) {
      if (command[i] == '0') {
        transmit(false, PULSE_LOW);
        transmit(true, PULSE_LOW);
        transmit(false, PULSE_LOW);
      }

      // If current bit is 1, transmit LOW-HIGH-HIGH (011):
      if (command[i] == '1') {
        transmit(false, PULSE_LOW);
        transmit(true, PULSE_HIGH);
      }  
  }
  for(int repeat = 0; repeat < REPEAT_TIMES-1; repeat++)
  {
  transmit(true, AGC1_PULSE);
  transmit(false, AGC2_PULSE);
  transmit(true, AGC3_PULSE);

  for (int i = 0; i < COMMAND_BIT_ARRAY_SIZE; i++) {
      if (command[i] == '0') {
        transmit(false, PULSE_LOW);
        transmit(true, PULSE_LOW);
        transmit(false, PULSE_LOW);
      }

      // If current bit is 1, transmit LOW-HIGH-HIGH (011):
      if (command[i] == '1') {
        transmit(false, PULSE_LOW);
        transmit(true, PULSE_HIGH);
      }  
  }
  }
  transmit(false, RADIO_SILENCE);
}

void transmit(bool level, int delay_microseconds) {
  if (level) {
    GPOS = (1 << TRANSMIT_PIN);  // Set pin HIGH
  } else {
    GPOC = (1 << TRANSMIT_PIN);  // Set pin LOW
  }
  delayMicroseconds(delay_microseconds);
}
