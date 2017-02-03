#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define PIN 5

SoftwareSerial BT(10, 11);
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ400);

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
String BTGelen;
char BTGelenC;
String getReplace(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop()
{
  while (BT.available() > 0) {
    BTGelenC = BT.read();
    if (BTGelenC == 'r') {
      //Kırmızı
      colorWipe(strip.Color(0, 255, 0));
      BT.print("Kirmizi\n");
    }
    else if (BTGelenC == 'g') {
      //Yeşil
      colorWipe(strip.Color(255, 0, 0));
      BT.print("Yesil\n");
    }
    else if (BTGelenC == 'b') {
      //Mavi
      colorWipe(strip.Color(0, 0, 255));
      BT.print("Mavi\n");
    }
    else if (BTGelenC == 'w') {
      //Beyaz
      colorWipe(strip.Color(255, 255, 255));
      BT.print("Beyaz\n");
    } else if (BTGelenC == 'c') {
      //Kapat
      colorWipe(strip.Color(0, 0, 0));
      BT.print("Kapandi\n");
    } else if (BTGelenC == 'y') {
      //Geçiş Efekti
      BT.print("Efekt basladi\n");
      rainbow(20);
    } else {
      //RGB Renk paleti
      BTGelen = BT.readString();
      //Gelen String veriyi parçaladık.
      String R = getReplace(BTGelen, ':', 0);
      String G = getReplace(BTGelen, ':', 1);
      String B = getReplace(BTGelen, ':', 2);
      colorWipe(strip.Color(G.toInt(), R.toInt(), B.toInt()));
      //
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
