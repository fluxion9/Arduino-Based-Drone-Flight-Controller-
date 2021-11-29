String received, Values;
unsigned long convertedValue;
int motor1 = 5;
int motor2 = 9;
int motor3 = 10;
int motor4 = 11;
int motorSpeed1, motorSpeed2, motorSpeed3, motorSpeed4;
int blinkingLED = 8;
int buzzer = 12;

class Flasher
{
  int ledPin;
  long onTime;
  long offTime;

  int ledState;
  unsigned long previousMillis;
  public:
  Flasher(int pin, long on, long off)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);

    onTime = on;
    offTime = off;
    ledState = LOW;
    previousMillis = 0;
  }
  void Update()
  {
    unsigned long currentMillis = millis();
    if((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
    {
      ledState = LOW;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
    {
      ledState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, ledState);
    }
  }
};


Flasher flash(blinkingLED, 200, 5000);
void setup() {
  Serial.begin(9600);
  Initialize();
  testMotors();
}

void loop() {
  flash.Update();
  receiveValues();
  convertToInt();
  splitInt(convertedValue, 8);
  reMapSpeeds(0, 254);
  writeSpeeds(motor1, motor2, motor3, motor4);
}
void receiveValues()
{
  while(Serial.available())
  {
    delay(3);
    char data = Serial.read();
    received += data;
  }
  if(received.length() > 0)
  {
    Values = received;
    received = "";
  }
}

void convertToInt()
{
  convertedValue = Values.toInt();
}
void splitInt(unsigned long num, int Length)
{
  long first, second, third, fourth, fifth, sixth, seventh, eight;
  first = long(num / long(pow(10, Length - 1)));
  second = long(num / long(pow(10, Length - 2)));
  second = second - (long(second / 10) * 10);
  third = long(num / long(pow(10, Length - 3)));
  third = third - (long(third / 10) * 10);
  fourth = long(num / long(pow(10, Length - 4)));
  fourth = fourth - (long(fourth / 10) * 10);
  fifth = long(num / long(pow(10, Length - 5)));
  fifth = fifth - (long(fifth / 10) * 10);
  sixth = long(num / long(pow(10, Length - 6)));
  sixth = sixth - (long(sixth / 10) * 10);
  seventh = long(num / long(pow(10, Length - 7)));
  seventh = seventh - (long(seventh / 10) * 10);
  eight = num - (long(num / 10) * 10);
  motorSpeed1 = (first * 10) + second;
  motorSpeed2 = (third * 10) + fourth;
  motorSpeed3 = (fifth * 10) + sixth;
  motorSpeed4 = (seventh * 10) + eight;
}
void reMapSpeeds(int Min, int Max)
{
  motorSpeed1 = map(motorSpeed1, 0, 99, Min, Max);
  motorSpeed2 = map(motorSpeed2, 0, 99, Min, Max);
  motorSpeed3 = map(motorSpeed3, 0, 99, Min, Max);
  motorSpeed4 = map(motorSpeed4, 0, 99, Min, Max);
}
void writeSpeeds(int m1, int m2, int m3, int m4)
{
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  analogWrite(m1, motorSpeed1);
  analogWrite(m2, motorSpeed2);
  analogWrite(m3, motorSpeed3);
  analogWrite(m4, motorSpeed4);
}
void Initialize()
{
  delay(2000);
  pinMode(buzzer, OUTPUT);
  tone(buzzer, 2000);
  for(int i = 0; i < 3; i+=1)
  {
    digitalWrite(blinkingLED, 1);
    delay(500);
    digitalWrite(blinkingLED, 0);
    delay(500);
  }
  noTone(buzzer);
}
void testMotors()
{
  delay(1000);
  runnMotor(motor1);
  beep();
  runnMotor(motor2);
  beep();
  runnMotor(motor3);
  beep();
  runnMotor(motor4);
  beep();
}
void beep()
{
  pinMode(blinkingLED, OUTPUT);
  digitalWrite(blinkingLED, 1);
  tone(buzzer, 2000);
  delay(300);
  noTone(buzzer);
  digitalWrite(blinkingLED, 0);
  delay(1500);
}
void runnMotor(int motor)
{
  analogWrite(motor, 100);
  delay(500);
  analogWrite(motor, 0);
}
