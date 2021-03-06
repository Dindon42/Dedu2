int IlluminateActiveExtinguishNonActive(int NbInputs)
{
  int NumActive=0;
  for (int i=0; i<=NbInputs ;i++)
  {
    if (ReadPlayerInput(i))
    {
      NumActive++;
      ActivateRedLight(i);
      InputState[i]=true;
      OutputState[i]=true;
    }
    else
    {
      DeactivateRedLight(i);
      InputState[i]=false;
      OutputState[i]=false;
    }
  }
  return NumActive;
}

//Reads all input pins, if HIGH, deactivate the OUTPUT. Return the number of output switched.
int ReadInputDeactivateOutputIfActive(int NbInputs)
{
  int count=0;
  for (int i=0; i<=NbInputs; i++)
  {
    if (ReadPlayerInput(i))
    {
      if (ReadPlayerOutput(i))
      {
        //Deactivate the output
        DeactivateRedLight(i);
        count++;
      }
      
    }
  }
  return count;
}

//Reads each user input.  If the input is Active, toggle the light.
void ReadInputToggleOutput(int NbInputs)
{
  for (int i=0; i<=NbInputs; i++)
  {
    if (ReadPlayerInput(i))
    {
      if (ReadPlayerOutput(i))
      {
        DeactivateRedLight(i);
      }
      else
      {
        ActivateRedLight(i);
      }
    }
  }
}

//Returns HIGH or LOW
bool ReadPlayerInput(int iPlayer)
{
  bool ReverseInput=iPlayer==JoueurPuissant;
  bool Input = digitalRead(PlayerInputPins[iPlayer])==HIGH;

  return ReverseInput ? !Input : Input;
}

//Returns HIGH or LOW
bool ReadPlayerOutput(int iPlayer)
{
  return digitalRead(PlayerOutputPins[iPlayer])==HIGH;
}

bool ToggleOutput(int iPlayer)
{
  if (ReadPlayerOutput(iPlayer))
  {
    DeactivateRedLight(iPlayer);
    return false;
  }
  else
  {
    ActivateRedLight(iPlayer);
    return true;
  }
}

//Return first active player.  -1 is default if none active.  Player 1 is 0.
int FirstActive(int NbInputs)
{
  for (int i=0; i<=NbInputs; i++)
  {
    if (ReadPlayerInput(i))
    {
      return i;
    }
  }
  return -1;
}

//Returns the number of active inputs.  0 is default if none.
int CheckAllActive(int NbInputs)
{
  int NumActive=0;
  for (int i=0; i<=NbInputs; i++)
  {
    //Store in global input array
    InputState[i]=ReadPlayerInput(i);
    if (InputState[i])
    {
      NumActive++;
    }
  }
  return NumActive;
}

//Checks the active outputs, returns the number of active.
int CheckAllActiveOutputs(int NbOutputs)
{
  int NumActive=0;
  for (int i=0; i<=NbOutputs; i++)
  {
    //Store in global output array
    OutputState[i]=ReadPlayerOutput(i);
    if (OutputState[i])
    {
      NumActive++;
    }
  }
  return NumActive;
}

//Return first active player output.  -1 is default if none active.  Player 1 is 0.
int FirstActiveOutput(int NbOutputs)
{
  for (int i=0; i<=NbOutputs; i++)
  {
    if (ReadPlayerOutput(i))
    {
      return i;
    }
  }
  return -1;
}

//Waits for all inputs to be non-active or MAX ITER, in which case, error mode.
void WaitForAllNonActive(int NbInputs)
{
  int max_iter=60;
  int count=0;
  
  do
  {
    count++;
    delay(15);
  }while(CheckAllActive(nbj_raw)!=0 && count<=max_iter);
  
  if (count>=max_iter)
  {
    FlashAndBuzzAllActive();
    WaitForAllNonActive(NbInputs);
  }

  TurnOffAllRedLights();
  
}

