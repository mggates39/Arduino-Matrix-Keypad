#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Key.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOCK_RELAY_PIN 10
#define BUZZER_PIN 11

#define NOTE_G4 392
#define NOTE_D5 587
#define NOTE_C6 1047

#define Password_Length 8

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

char Data[Password_Length];
char Master[Password_Length] = "123A456";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  pinMode(LOCK_RELAY_PIN, OUTPUT);
  digitalWrite(LOCK_RELAY_PIN, HIGH);

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  display.display();
}

void loop()
{
  display.setCursor(0, 0);
  display.setTextSize(1); // Draw normal-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("Enter Password:"));
  display.display();

  customKey = customKeypad.getKey();

  if (customKey)
  {
    tone(BUZZER_PIN, 33);
    Data[data_count] = customKey;
    display.setCursor(data_count * 8, 20);
    display.print('*');
    display.display();
    data_count++;
    noTone(BUZZER_PIN);
  }

  if (data_count == Password_Length - 1)
  {
    display.clearDisplay();
    display.setCursor(0, 0);

    if (!strcmp(Data, Master))
    {
      display.setTextSize(2); // Draw 2X-scale text
      display.print("  Welcome");
      display.display();
      Serial.println("Open");
      digitalWrite(LOCK_RELAY_PIN, LOW);
      tone(BUZZER_PIN, NOTE_D5);
      delay(500);
      tone(BUZZER_PIN, NOTE_G4);
      delay(500);
      noTone(BUZZER_PIN);
      delay(4000);
      digitalWrite(LOCK_RELAY_PIN, HIGH);
    }
    else
    {
      display.setTextSize(2); // Draw 2X-scale text
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.print("  Access  \n  Denied  ");
      display.display();
      Serial.println("Failed");
      tone(BUZZER_PIN, NOTE_C6);
      delay(2000);
      noTone(BUZZER_PIN);
    }
    clearData();
    display.clearDisplay();
  }
}

void clearData()
{
  while (data_count != 0)
  {
    Data[data_count--] = 0;
  }
  return;
}
