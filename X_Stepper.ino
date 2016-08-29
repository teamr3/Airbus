

void stepX()
{
  digitalWrite(xStepperStep,LOW);
  delayMicroseconds(100);
  digitalWrite(xStepperStep,HIGH);
  delayMicroseconds(150);
}
//
//void step1Med()
//{
//  digitalWrite(stepper1Step,LOW);
//  delayMicroseconds(2000);
//  digitalWrite(stepper1Step,HIGH);
//  delayMicroseconds(4000);
//}
//
//void step1Fast()
//{
//  digitalWrite(stepper1Step,LOW);
//  delayMicroseconds(600);
//  digitalWrite(stepper1Step,HIGH);
//  delayMicroseconds(1200);
//}

int moveX(double distance)
{
   /*
   *  X Stepper
   *  HIGH = LEFT
   *  LOW = RIGHT
  */
  double mmPerPulse = 0.0025796;
  //int delayDur = 100;
  double magnitude = fabs(distance);
  digitalWrite(xStepperDir, (distance < 0)?HIGH:LOW);
  
  long numPulses = long(round(magnitude/mmPerPulse));
  //Serial.print(numPulses);

  if (numPulses == 0)
  {
    return 0; //If we aren't going to send pulses, we can leave
  }
  
  for (long i = 0;i < numPulses; i++)
  {
//    if(digitalRead(lsE)==HIGH || digitalRead(lsF)==HIGH)
//    {
//      digitalWrite(led,HIGH);
//      return 1;
//    }
//    else if(digitalRead(pauseButton) == HIGH)
//    {
//      handlePauseButton();
//    }
    
    digitalWrite(xStepperStep, LOW);
    delayMicroseconds(100);
    digitalWrite(xStepperStep, HIGH);
    delayMicroseconds(150);

    if (!encodersEnabled)
    {
      localXPosition += mmPerPulse * distance/magnitude;
      absoluteXPosition += mmPerPulse * distance/magnitude;
    }
  }
    
  return 0;
}
