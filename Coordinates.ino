void mirrorX()
{
  for (int i = 0; i < 3; i++)
  {
    datumHoles[i][0] = -datumHoles[i][0]; 
  }

  for (int i = 0; i < 10; i++)
  {
    constrainedHoles[i][0] = -constrainedHoles[i][0]; 
  }

  for (int i = 0; i < 252; i++)
  {
    patternCoords[i][0] = -patternCoords[i][0]; 
  }
  return;
}

void rotateCoords()
{
  float currentX;
  float angleSin = sin(plateAngle * 0.0174533); //Trig functions take radian args
  float angleCos = cos(plateAngle * 0.0174533);

  for (int i = 0; i < 3; i++)
  {
    //Rotate datum holes
    currentX = datumHoles[i][0];
    datumHoles[i][0] = angleCos*currentX+ angleSin*datumHoles[i][1]; 
    datumHoles[i][1] = -1.0*angleSin*currentX + angleCos*datumHoles[i][1];
  }

  for (int i = 0; i < 10; i++)
  {
    //Rotate constrained holes
    currentX = constrainedHoles[i][0];
    constrainedHoles[i][0] = angleCos*currentX+ angleSin*constrainedHoles[i][1]; 
    constrainedHoles[i][1] = -1.0*angleSin*currentX + angleCos*constrainedHoles[i][1];
  }

  for (int i = 0; i < 252; i++)
  {
    //Rotate main hole pattern
    currentX = patternCoords[i][0];
    patternCoords[i][0] = angleCos*currentX+ angleSin*patternCoords[i][1]; 
    patternCoords[i][1] = -1.0*angleSin*currentX + angleCos*patternCoords[i][1];
  }
}

void homeMachine()
{
  digitalWrite(yStepperDir, HIGH); //Going down
  while(digitalRead(lsD) == LOW)
  {
    handlePauseButton();
    stepY();
  }
  if(digitalRead(lsD)==HIGH)
    digitalWrite(led, HIGH);
  else
    while(true)
    {
      digitalWrite(led,HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
    }

  digitalWrite(xStepperDir, HIGH); //Going left
  while(digitalRead(lsF) == LOW)
  {
    handlePauseButton();
    stepX();
  }

  absoluteXPosition = 0.0;
  absoluteYPosition = 0.0;

  comeOffLimits(); //Move functions will only work once limit switches are off
}

void comeOffLimits()
{
  double mmPerPulse = 0.0025796;
  
  if (digitalRead(lsC) == HIGH)
  {
    digitalWrite(yStepperDir, HIGH); //Going down
    while(digitalRead(lsC) == HIGH)
    {
      handlePauseButton();
      stepY();
      absoluteYPosition -= mmPerPulse;
    }
  }
  else if (digitalRead(lsD) == HIGH)
  {
    digitalWrite(yStepperDir, LOW); //Going up
    while(digitalRead(lsD) == HIGH)
    {
      handlePauseButton();
      stepY();
      absoluteYPosition += mmPerPulse;
    }
  }

  if (digitalRead(lsE) == HIGH)
  {
    digitalWrite(xStepperDir, HIGH); //Going left
    while(digitalRead(lsE) == HIGH)
    {
      handlePauseButton();
      stepX();
      absoluteXPosition -= mmPerPulse;
    }
  }
  else if (digitalRead(lsF) == HIGH)
  {
    digitalWrite(xStepperDir, LOW); //Going right
    while(digitalRead(lsF) == HIGH)
    {
      handlePauseButton();
      stepX();
      absoluteXPosition += mmPerPulse;
    }
  }
}

void seekDatum()
{
  float offsetX = 0.0;
  float offsetY = 0.0;
  
  if (plateAngle == 0.0)
  {
    //Go for primary datum hole
    offsetX = datumHoles[0][0]+350.0 - absoluteXPosition; //Will need to play with offsets to position camera roughly over hole
    offsetY = datumHoles[0][1]+350.0 - absoluteYPosition; 
  }  
  else if (plateAngle == -90.0)
  {
    //Pick a hole to go for
    offsetX = datumHoles[0][0]+350.0 - absoluteXPosition; //Will need to play with offsets to position camera roughly over hole
    offsetY = datumHoles[0][1]+350.0 - absoluteYPosition; 
  }
  else if (plateAngle == -180.0)
  {
    //
    offsetX = datumHoles[2][0]+350.0 - absoluteXPosition; //Will need to play with offsets to position camera roughly over hole
    offsetY = datumHoles[2][1]+350.0 - absoluteYPosition; 
  }
  else if (plateAngle == -270.0)
  {
    //
    offsetX = datumHoles[0][0]+350.0 - absoluteXPosition; //Will need to play with offsets to position camera roughly over hole
    offsetY = datumHoles[0][1]+350.0 - absoluteYPosition; 
  }

  moveX(offsetX);
  moveY(offsetY);
}

