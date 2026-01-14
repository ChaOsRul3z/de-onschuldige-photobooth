/*
  
  Arduino demo SPI code for 16X PWM LED FADER
  
  support@CuriousInventor.com
  (c) 2011, Curious Inventor, LLC
  
  Instructions: check out read_serial_port() for some examples
  
  change log: 
  1/14/11 - initial release

 */
char print_text[60] = "16X PWM LED FADER demo SPI arduino control, v1.0, 1/14/11";
 
// __________  DEFINES __________________________________________
#define MOSI 11//data
#define MISO 12//data
#define PICLOCK  13//sck
#define SLAVESELECT 10//ss
#define SERIAL 1\..._____

#include <avr/pgmspace.h>

 
// __________  GLOBALS __________________________________________
int command = 0;
unsigned int channel = 0;
unsigned int brightness = 0;
unsigned int speed = 0;
unsigned int fade = 0;
unsigned int group = 0;
unsigned int mask = 0;
unsigned int loops = 0;

// function prototypes
void spi_init();
char spi_transfer(volatile char data);
void read_serial_port();
void start_blink(unsigned int channel, unsigned int bri, unsigned int spd);
void start_fade(unsigned int channel, unsigned int bri, unsigned int spd);
void stop_channel(unsigned int channel);
void set_channel(unsigned int channel, unsigned int bri);
void start_random_blink_group(int group, unsigned int bri, unsigned int spd);

void setup()
{
  Serial.begin(9600);
  spi_init();
  Serial.println(print_text);
}

void loop()
{
  read_serial_port();
}

void read_serial_port()
{
  if (Serial.available() > 0)
  {
    command = Serial.parseInt();
    channel = Serial.parseInt();
    brightness = Serial.parseInt();
    speed = Serial.parseInt();

    switch (command)
    {
      case 1:
        set_channel(channel, brightness);
        break;

      case 2:
        start_blink(channel, brightness, speed);
        break;

      case 3:
        start_fade(channel, brightness, speed);
        break;

      case 4:
        stop_channel(channel);
        break;
    }
  }
}

void spi_init()
{
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(PICLOCK, OUTPUT);
  pinMode(SLAVESELECT, OUTPUT);

  digitalWrite(SLAVESELECT, HIGH);

  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void set_channel(unsigned int channel, unsigned int bri)
{
  spi_transfer(0x01);
  spi_transfer(channel);
  spi_transfer(bri >> 8);
  spi_transfer(bri & 0xFF);
}

void start_blink(unsigned int channel, unsigned int bri, unsigned int spd)
{
  spi_transfer(0x02);
  spi_transfer(channel);
  spi_transfer(bri >> 8);
  spi_transfer(bri & 0xFF);
  spi_transfer(spd >> 8);
  spi_transfer(spd & 0xFF);
}

void start_fade(unsigned int channel, unsigned int bri, unsigned int spd)
{
  spi_transfer(0x03);
  spi_transfer(channel);
  spi_transfer(bri >> 8);
  spi_transfer(bri & 0xFF);
  spi_transfer(spd >> 8);
  spi_transfer(spd & 0xFF);
}

void stop_channel(unsigned int channel)
{
  spi_transfer(0x04);
  spi_transfer(channel);
}

char spi_transfer(volatile char data)
{
  digitalWrite(SLAVESELECT, 0);
  SPDR = data;
  while (!(SPSR & (1<<SPIF)))
  {
  };
  digitalWrite(SLAVESELECT, 1);
  return SPDR;
}
