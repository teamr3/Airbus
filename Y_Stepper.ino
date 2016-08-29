void stepY()
{
  digitalWrite(yStepperStep,LOW);
  delayMicroseconds(200);
  digitalWrite(yStepperStep,HIGH);
  delayMicroseconds(200);
}
//
//void step2Med()
//{
//  digitalWrite(stepper2Step,LOW);
//  delayMicroseconds(2000);
//  digitalWrite(stepper2Step,HIGH);
//  delayMicroseconds(4000);
//}
//
//void step2Fast()
//{
//  digitalWrite(stepper2Step,LOW);
//  delayMicroseconds(600);
//  digitalWrite(stepper2Step,HIGH);
//  delayMicroseconds(1200);
//}

int moveY(double distance)
{
   /*
   *  Y Stepper
   *  HIGH = DOWN
   *  LOW = UP
  */
  double mmPerPulse = 0.0025796;
  double magnitude = fabs(distance);
  digitalWrite(yStepperDir, (distance < 0)?HIGH:LOW);
  
  long numPulses = long(round(magnitude/mmPerPulse));

  if (numPulses == 0)
  {
    return 0; //If we aren't going to send pulses, we can leave
  }
  
  for (long i = 0;i < numPulses; i++)
  {
//    if(digitalRead(lsC)==HIGH || digitalRead(lsD)==HIGH)
//    {
//      digitalWrite(13,HIGH);
//      return 1;
//    }
//    else if(digitalRead(pauseButton) == HIGH)
//    {
//      handlePauseButton();
//    }
    
    digitalWrite(yStepperStep, LOW);
    delayMicroseconds(100);
    digitalWrite(yStepperStep, HIGH);
    delayMicroseconds(150);

    if (!encodersEnabled)
    {
      localYPosition += mmPerPulse * distance/magnitude;
      absoluteYPosition += mmPerPulse * distance/magnitude;
    }

  }
    
  return 0;
}
