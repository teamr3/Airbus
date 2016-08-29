void faultDisplay(int faultCode)
{
  digitalWrite(led, LOW);
  switch(faultCode)
  {
    case 1:
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      break;
    default:
      break;
  }
  return;
}

