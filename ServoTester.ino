#include <Servo.h>
#include <movingAvg.h>

Servo servo;
movingAvg meter(5);

const int PIN_SERVO = 10;

void setup() {
  servo.attach( PIN_SERVO );
  Serial.begin(9600);
  meter.begin();

}

void loop() {
  int nPos = analogRead( A0 );

  int meterAvg = meter.reading(nPos);

  Serial.print(", meterAvg: ");
  Serial.println(meterAvg);

  int angle = map( meterAvg, 0, 1023, 0, 180 );

  servo.write( angle );

  Serial.print(", angle: ");
  Serial.println(angle);
  
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