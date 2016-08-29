int scanSerial()
{
  if(Serial.read() == 'A')
  {
    int val1 = Serial.parseInt();
    int val2 = Serial.parseInt();
    int val3 = Serial.parseInt();
    if(Serial.read() == 'x')
    {
      currentXoffset = val1;
      currentYoffset = val2;
      blobCounter = val3;
    }
    Serial.print("Read: ");
    Serial.print(val1);
    Serial.print(val2);
    Serial.print(val3);
     if(blobCounter != 1)
     {
      if(currentColour > 9)
      {
        currentColour = 0;
      }
       currentColour++;
       //setColour(8);
       return 1; //Things look funky or don't look like anything, keep trying
     }

     return 0; //One blob seen, le'go
  }
  else
  {
    return -1; //Camera's not sending a communication
  }
}

void requestData()
{
  Serial.print("R");
}

