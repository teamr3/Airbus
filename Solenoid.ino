void fireBigBen()
{
  digitalWrite(bigBenPin, LOW);
  delay(5000);
}

void retractBigBen()
{
  digitalWrite(bigBenPin, HIGH);
  delay(2000);
}

void drillsOn()
{
  digitalWrite(drillPin, LOW);
  delay(500);
  return;
}

void drillsOff()
{
  digitalWrite(drillPin, HIGH);
  return;
}

int quillDown()
{
  digitalWrite(quillSolPin, LOW);
  return 0;
}

int quillUp()
{
  digitalWrite(quillSolPin, HIGH);
  return 0;
}

int housingDown()
{
  digitalWrite(housingSolPin, LOW);
  return 0;
}

int housingUp()
{
  digitalWrite(housingSolPin, HIGH);
  return 0;
}

int fullDrillCycle()
{
  long startTime;
  
  drillsOn();
  housingDown();

  startTime = millis(); //Note drilling start time

  /*
   * NEED TO CONFIRM WHICH LS IS WHICH
   */

  //Drill until the drills down LS is made
  while(digitalRead(lsB)==LOW)
  {
    handlePauseButton();
    drillsOn();
    housingDown();
    //Abort if drill time is over 30 secs, return error
    if(millis() - startTime > 30 * 1000)
    {
      digitalWrite(led, HIGH);//Error timeout
      drillsOff();
      housingUp();
      return 1;
    }
  }

//delay(10000); //PPA drill for a while, hope you break through

  housingUp();
  delay(500);
  drillsOff();
  delay(500);
  return 0;
}

int quillDrillCycle()
{
  long startTime;
  
  drillsOn();
  delay(100);
  quillDown();

  startTime = millis();

  /*
   * NEED TO CONFIRM WHICH LS IS WHICH
   */

  //Drill until the drills down LS is made
//  while(digitalRead(lsA)==LOW)
//  {
//    handlePauseButton();
//    drillsOn();
//    quillDown();
//    //Abort if drill time is over 30 secs, return error
//    if(millis() - startTime > 30 * 1000)
//    {
//      digitalWrite(led, HIGH);//Error timeout
//      drillsOff();
//      housingUp();
//      return 1;
//    }
//  }

delay(20000);

  //delay(14000);//PPA drill for a while

  quillUp();
  delay(500);
  drillsOff();
  delay(500);
  return 0;
}

