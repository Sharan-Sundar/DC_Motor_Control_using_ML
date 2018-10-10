
int sensorPin = 2;
unsigned long  start = 0;
unsigned long  prevmillis = 0;
unsigned long  prevmillis1 = 0;
unsigned long duration = 0;
unsigned long  start1 = 0;
unsigned long  prevmillis2 = 0;
unsigned long duration1 = 0;
long double a[8] = { -0.00000000000000004896076306, 0.0000000000001776535881, -0.0000000002544361229, 0.0000001818911868, -0.00006673336303, 0.01132983218, -0.4984069244, 0.0148070398};
//long double a[8]={-0.0000000000000001034462086,0.0000000000004050112469,-0.0000000006368041123,0.0000005110427375,-0.0002178751315,0.04573793917,-3.41972431,0.001592715736};
//long double b[5]={0.0000000001520883262,0.0000002351627109,-0.0003473543431,0.2014652198,-0.3950422092};
float rpm = 0;
float rrpm = 0;
float rrpm1, maxrpm;
float pwm = 0;
float pwm1 = 0;
const int motor = 11;
int i = 0;
int count = 0;
int diff = 0;
int f = 0;
//int min,max;
//int flag=0;
//int flag1=0;


void setup()
{
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  prevmillis = 0;
  attachInterrupt(0, pin_ISR1, RISING);
  analogWrite(motor, 255);
  delay(2000);
  maxrpm = (60000000 / duration1);
  Serial.print("MAX RPM:");
  Serial.println(maxrpm);
  detachInterrupt(pin_ISR1);
  attachInterrupt(0, pin_ISR, RISING);
}


void loop()
{

  while (Serial.available())
  {
    rrpm = Serial.parseInt();
    rrpm1 = (maxrpm / 1020) * rrpm; //1.34=maxrpm of new motor/max rpm of my motor's rpm=1020
    if (rrpm1 == 0)
      pwm = 0;
    else
    {
      pwm = a[0];
      for (i = 1; i < 8; i++)
      {
        pwm = pwm * rrpm1 + a[i]; //use rrpm1 instead of rpm
      }
      if (pwm > 255)
        pwm = 255;
      else if (pwm < 20)
        pwm = 20;
    }
    Serial.println("START");
  }

  analogWrite(motor, pwm);


  //Serial.println("Required RPM: ");
  //Serial.print(rrpm);
  if (count == 1)
  { duration = ( micros() - prevmillis );
    prevmillis = micros();
    rpm = (60000000 / duration);
    //Serial.println("Current RPM: ");
    if(rpm<maxrpm)
    {
    Serial.println(rpm);
    //Serial.print("     ");
       Serial.print(millis());
       Serial.print("      ");
    }
    //Serial.println("PWM value: ");
    //Serial.println(pwm);
    count = 0;
  }


  if (rpm < maxrpm)
  {
    if (millis() - prevmillis1 > 400)
    {
      diff = abs(rrpm - rpm);
      if (rpm < rrpm - 5)
      { if (rpm > (maxrpm / 2))
        {
          if (diff < 10)
            pwm++;
          else if (diff > 10 && diff < 60)
            pwm += diff / 2.74;
          else
            pwm += diff / 2.74;
          if (pwm > 255)
            pwm = 255;
          //analogWrite(motor, pwm);
        }
        else
        {
          if (diff < 10)
            pwm++;
          else if (diff > 10 && diff < 60)
            pwm += diff / 8.91;
          else
            pwm += diff / 8.91;
          if (pwm > 255)
            pwm = 255;
          //analogWrite(motor, pwm);
        }
      }
      if (rpm > rrpm + 5)
      {
        if (rpm > (maxrpm / 2))
        {
          if (diff < 10)
            pwm--;
          else if (diff > 10 && diff < 60)
            pwm -= diff / 2.74;
          else
            pwm -= diff / 2.74;
          if (pwm < 20)
            pwm = 20;
        }
        else
        {
          if (diff < 10)
            pwm--;
          else if (diff > 10 && diff < 60)
            pwm -= diff / 8.91;
          else
            pwm -= diff / 8.91;
          if (pwm < 20)
            pwm = 20;
        }
      }
      prevmillis1 = millis();
    }
    //analogWrite(motor, pwm);


    if (rrpm == 0)
      pwm = 0;
  }
  // else
  //analogWrite(motor, pwm);

}
void pin_ISR1()
{
  duration1 = ( micros() - prevmillis2 );
  prevmillis2 = micros();
}

void pin_ISR()
{
  count = 1;
}

