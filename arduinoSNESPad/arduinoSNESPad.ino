// BIT DEFINITIONS
#define SNES_B       0x01
#define SNES_Y       0x02
#define SNES_SELECT  0x04
#define SNES_START   0x08
#define SNES_UP      0x10
#define SNES_DOWN    0x20
#define SNES_LEFT    0x40
#define SNES_RIGHT   0x80
#define SNES_A       0x100
#define SNES_X       0x200
#define SNES_L       0x400
#define SNES_R       0x800

int buttons();
void strobe();
int shiftin();

int state = 0;

// PINS
int latch = 2; // set the latch pin
int clock = 3; // set the clock pin
int datin = 4;// set the data in pin
byte controller_data = 0;
int ledpin = 13;


// SETUP
void setup() {
  Serial.begin(57600);
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(datin,INPUT);
  pinMode(ledpin, OUTPUT);
  
  digitalWrite(latch,HIGH);
  digitalWrite(clock,HIGH);
}

// FUNCTIONS
void strobe(void)
{
  digitalWrite(latch, HIGH);
  delayMicroseconds(12);
  digitalWrite(latch, LOW);
}

int shiftin(void)
{
  int ret = digitalRead(datin);
  delayMicroseconds(12);
  digitalWrite(clock, HIGH);
  delayMicroseconds(12);
  digitalWrite(clock, LOW);
  return ret;
}

int buttons(void)
{
  int ret = 0;
  byte i;
  strobe();
  for (i = 0; i < 16; i++) {
    ret |= shiftin() << i;
  }
  return ~ret;
}

// MAIN
void loop(){
  state = buttons();
  if (state & SNES_B)      Serial.print("0");
  if (state & SNES_Y)      Serial.print("1");
  if (state & SNES_SELECT) Serial.print("2");
  if (state & SNES_START)  Serial.print("3");
  if (state & SNES_UP)     Serial.print("4");
  if (state & SNES_DOWN)   Serial.print("5");
  if (state & SNES_LEFT)   Serial.print("6");
  if (state & SNES_RIGHT)  Serial.print("7");
  if (state & SNES_A)      Serial.print("8");
  if (state & SNES_X)      Serial.print("9");
  if (state & SNES_L)      Serial.print("A");
  if (state & SNES_R)      Serial.print("B");
  Serial.println();
  //Serial.println(state);
  delay(1);
}
