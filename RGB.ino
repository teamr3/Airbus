void setColour(int colourVal)
{
  if(colourVal == 0)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(0,0,64));
    pixels.show();
    }
  }

  if(colourVal == 1)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(0,0,127)); // 
    pixels.show();
    }
  }


  if(colourVal == 2)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(0,0,255)); // Blue
    pixels.show();
    }
  }

  if(colourVal == 3)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(127,0,0)); // 
    pixels.show();
    }
  }

  if(colourVal == 4)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Red
    pixels.show();
    }
  }

  if(colourVal == 5)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(0,127,0)); // 
    pixels.show();
    }
  }

  if(colourVal == 6)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(0,255,0)); // Green
    pixels.show();
    }
  }

  if(colourVal == 7)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(127,127,127)); //
    pixels.show();
    }
  }

  if(colourVal == 8)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(255,255,255)); // White
    pixels.show();
    }
  }

  if(colourVal == 9)
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Off
    pixels.show();
    }
  }
}

