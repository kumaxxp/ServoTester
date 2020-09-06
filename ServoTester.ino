#include <Servo.h>
#include <movingAvg.h>

Servo servo0;
Servo servo1;
Servo servo2;
movingAvg meter0(5);
movingAvg meter1(5);
movingAvg meter2(5);

const int PIN_SERVO_0 = 10;
const int PIN_SERVO_1 = 11;
const int PIN_SERVO_2 = 12;

void setup() {
  servo0.attach( PIN_SERVO_0 );
  servo1.attach( PIN_SERVO_1 );
  servo2.attach( PIN_SERVO_2 );
  meter0.begin();
  meter1.begin();
  meter2.begin();

  Serial.begin(9600);
}

void loop() {
  int nPos0 = analogRead( A0 );
  int meterAvg0 = meter0.reading(nPos0);

  int nPos1 = analogRead( A1 );
  int meterAvg1 = meter1.reading(nPos1);

  int nPos2 = analogRead( A2 );
  int meterAvg2 = meter2.reading(nPos2);

  Serial.print(", meterAvg: ");
  Serial.println(meterAvg1);

  int angle0 = map( meterAvg0, 0, 1023, 0, 180 );
  servo0.write( angle0);

  int angle1 = map( meterAvg1, 0, 1023, 0, 180 );
  servo1.write( angle1);

  int angle2 = map( meterAvg2, 0, 1023, 0, 180 );
  servo2.write( angle2);

  Serial.print(", angle: ");
  Serial.println(angle1);
  
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