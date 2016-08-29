int lookForHole()
{
  int scanResult = 1;
  int attempts = 0;
  int closeEnoughX = 5;
  int closeEnoughY = 5;

  for (int i = 0; i < 100; i++) //Try to reposition over hole a maximum of 10 times
  {
    scanResult = 1;
    while (scanResult != 0) //Comes back 0 when exactly 1 blob is seen
    {
      scanResult = scanSerial();
  
      attempts += 1;
  
      if (attempts > 1000000)
      {
        return -1; // Tried a million times, couldn't find the hole
      }
    }//end while
    attempts = 0;
  
    if (abs(currentXoffset) < closeEnoughX && abs(currentYoffset) < closeEnoughY) //Close enough
    {
      return 0; 
    }
  
    if(currentXoffset > 0)
    {
      //Adjust X
      moveX(cam2mm(currentXoffset));
    }
    else if(currentXoffset < 0)
    {
      //Adjust X
      moveX(cam2mm(currentXoffset));
    }
    
    if(currentYoffset > 0)
    {
      //Adjust y
      moveY(cam2mm(currentYoffset));
    }
    else if(currentYoffset < 0)
    {
      //Adjust y
      moveY(cam2mm(currentYoffset));
    }

    delay(1000);
    
    
  }

  localXPosition = 250.0 - cameraXOffset;
  localYPosition = 0.0 - cameraYOffset;
  
  
  setColour(9); //Turn lights off
  delay(2000);
  return 0;
  
}

float cam2mm(int pixelOffset)
{
  float scalingFactor = 1.0; //Figure out this scaling factor
  return float(pixelOffset) * scalingFactor; 
}

