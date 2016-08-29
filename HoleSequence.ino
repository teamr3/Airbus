int drillConstrainedHoles()
{
  float xOffset, yOffset;
  
  for (int i = 0; i < 10; i++)
  {
    //Calculate offset to the next constrained hole
    xOffset = localXPosition - constrainedHoles[i][0];
    yOffset = localYPosition - constrainedHoles[i][1];

    //Move to the hole 
    moveX(xOffset);
    delay(1000);
    moveY(yOffset);
    delay(1000);

    //Drill the hole, using only the quill drill
    quillDrillCycle();
    delay(1000);
  }

  return 0; 
}

int drillHolePattern()
{
  int centreHole = 3;
  float xOffset, yOffset;
  
  if (plateAngle == 0.0 || plateAngle ==  -180.0)
  {
    //
    for (centreHole = 3; centreHole < 252; centreHole += 7)
    {
      xOffset = localXPosition - patternCoords[centreHole][0];
      yOffset = localYPosition - patternCoords[centreHole][1];

      //Move to the hole 
      moveX(xOffset);
      delay(1000);
      moveY(yOffset);
      delay(1000);

      fullDrillCycle();
      delay(1000);
      for(int i=centreHole - 3; i<centreHole+3; i++)
        holeIsDrilled[i] = true;
    }
  }
  else if (plateAngle == -90.0 || plateAngle == -270.0)
  {
    float lowestXValue = 1000.0;
    int holesAtCurrentX[20];
    int numHoles = 0;
    int consecutiveHoles = 0;
    int startHole = 0;
    
    while(stillHolesToBeDrilled())
    {
      //Reset hole list
      for (int i = 0; i < 20; i++)
      {
        holesAtCurrentX[i] = -1;
      }
      
      //Find lowest x that hasn't been drilled
      lowestXValue = 1000.0;
      for (int i = 0; i < 252; i++)
      {
        //
        if(patternCoords[i][0] < lowestXValue && !holeIsDrilled[i])
        {
          lowestXValue = patternCoords[i][0];
        }
      }
      
      //Get all the indices of non complete holes at this x, sorted by y
      numHoles = 0;
      for(int i = 0; i < 252; i++)
      {
        if (patternCoords[i][0] == lowestXValue)
        {
          holesAtCurrentX[numHoles] = i;
          numHoles++;
        }
      }
      
      for (int i = 0; i < numHoles - 1; i++)
      {
        for(int j = 0; j < numHoles - (i+1); j++)
        {
          //
          if(patternCoords[holesAtCurrentX[j]][1] < patternCoords[holesAtCurrentX[j+1]][1])
          {
            //Swap
            holesAtCurrentX[19] = holesAtCurrentX[j+1];
            holesAtCurrentX[j+1] = holesAtCurrentX[j];
            holesAtCurrentX[j] = holesAtCurrentX[19];
          }
        }
      }

      consecutiveHoles = 0;
      startHole = 0;
      for (int i = 0; i < numHoles-1; i++)
      {
        //
        if(patternCoords[holesAtCurrentX[i+1]][1] - patternCoords[holesAtCurrentX[i+1]][1] > 25.0)
        {
          //
          consecutiveHoles = 0;
          startHole = i+1;
        }
        else
        {
          consecutiveHoles++;
        }

        if(consecutiveHoles == 7)
        {
          moveX(patternCoords[holesAtCurrentX[startHole+4]][0] - localXPosition);
          moveY(patternCoords[holesAtCurrentX[startHole+4]][1] - localYPosition);
          fullDrillCycle();
          for (int mark = startHole; mark < startHole + 7; mark++)
          {
            holeIsDrilled[holesAtCurrentX[mark]] = true;
          }
          break;
        }
      }

      if(consecutiveHoles < 7)
      {
        for(int i = 0; i < numHoles; i++)
        {
          moveX(patternCoords[holesAtCurrentX[i]][0] - localXPosition);
          moveY(patternCoords[holesAtCurrentX[i]][1] - localYPosition);
          quillDrillCycle();
          holeIsDrilled[holesAtCurrentX[i]] = true;
        }
      }
      //Look for a 7 hole pattern in these holes
      //If pattern exists, position centre, drillFullCycle
      //If no pattern, drill each hole with quill drill
      //Mark holes as drilled
    }
     
  }
  else
  {
    //Some arbitrary angle was input.. 
    ppaDrillHoles();
  }
  return 0;
}

int ppaDrillHoles()
{
  float xOffset, yOffset;
  
  for (int centreHole = 0; centreHole<252; centreHole++)
  {
    xOffset = localXPosition - patternCoords[centreHole][0];
    yOffset = localYPosition - patternCoords[centreHole][1];

    //Move to the hole 
    moveX(xOffset);
    delay(1000);
    moveY(yOffset);
    delay(1000);

    quillDrillCycle();
    delay(1000);

    holeIsDrilled[centreHole] = true;
  }

  return 0;
}

boolean stillHolesToBeDrilled()
{
  for(int i = 0; i < 252; i++)
  {
    if(!holeIsDrilled[i])
    {
      return true;
    }
  }

  return false;
}

