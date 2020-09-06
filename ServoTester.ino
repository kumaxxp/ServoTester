#include <Servo.h>
#include <movingAvg.h>

//  表示のため greiman SSD1306Ascii をインストールした
//  https://www.youtube.com/watch?v=9tBxXPTLM6Y
//  この動画参考に実装

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;
// OLED関連の宣言ここまで

Servo servo0;
Servo servo1;
Servo servo2;
movingAvg meter0(5);
movingAvg meter1(5);
movingAvg meter2(5);

const int PIN_SERVO_0 = 5;
const int PIN_SERVO_1 = 11;
const int PIN_SERVO_2 = 12;

void setup() {
  servo0.attach( PIN_SERVO_0 );
  servo1.attach( PIN_SERVO_1 );
  servo2.attach( PIN_SERVO_2 );
  meter0.begin();
  meter1.begin();
  meter2.begin();

//  Serial.begin(9600);

  //  ↓ OLEDの設定
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled.setFont(Adafruit5x7);

  uint32_t m = micros();
  oled.clear();
  // first row
  oled.println("set1X test");

  // second row
  oled.set2X();
  oled.println("set2X test");

  // third row
  oled.set1X();
  oled.print("micros: ");
  oled.print(micros() - m);

}

void loop() {
  int nPos0 = analogRead( A0 );
  int meterAvg0 = meter0.reading(nPos0);

  int nPos1 = analogRead( A1 );
  int meterAvg1 = meter1.reading(nPos1);

  int nPos2 = analogRead( A2 );
  int meterAvg2 = meter2.reading(nPos2);

  //  移動平均を計算しているが、現在は使用していない

  int angle0 = map( nPos0, 0, 1023, 0, 180 );
  servo0.write( angle0);

  int angle1 = map( nPos1, 0, 1023, 0, 180 );
  servo1.write( angle1);

  int angle2 = map( nPos2, 0, 1023, 0, 180 );
  servo2.write( angle2);


  static int s_cnt = 0;
  s_cnt++;
  if(s_cnt == 10)
  {
    oled.clear();
    // first row
    oled.set1X();
    oled.print("ang: ");
    oled.println(angle0);

    // second row
    oled.set1X();
    oled.print("ang: ");
    oled.println(angle1);

    // third row
    oled.set1X();
    oled.print("ang: ");
    oled.println(angle2);

    s_cnt = 0;
  }
  
  delay(10);
}

/*
void loop() {
//  int angle = map( nPos, 0, 1023, -120, 120 );

  myservo.write( 0 );
  delay(10000);

  myservo.write( 180 );
  delay(10000);

}
*/