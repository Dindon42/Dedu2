int CalculDelaiFraudeur(bool iNormalDelay)
{
  if(iNormalDelay)  return random(50,80) + (11 - vitesse) * random(100);
  else return random(25,50) + (11 - vitesse) * random(50);
}

void Delay_Fraudeur(unsigned int NumRoundsToWait)
{
  bool PreviousState[nbj];
  //Debut DELAY et TESTFRAUDEUR --------------------------------------
  
  //Boucle d'attente entre les jeux.
  //Normalement: faire un countdown tranquille pendant que le temps s'écoule.
  //Si qqn clique, illuminer sa lumière et monter le DEDU.
  //Si d'autres cliquent, illuminer leur lumière.
  //Si le roi clique, illuminer les LED en alternance 0,1,2,3,0...
  //À la fin, envoyer le choix du roi.
  unsigned int RoundCounter=0;
  unsigned int LightOffCounter=0;
  #define FraudeurExtraRoundsMin  60
  #define FraudeurExtraRoundsMax 100
  #define PetitFraudeurExtraRoundsMin  5
  #define PetitFraudeurExtraRoundsMax 20
  int ExtraDelai;
  #define RoiLumiere false
  int SelectedGameType=-1;
  unsigned int GameTypeSelLightOffCounter=0;
  #define Delai_GameTypeSel 10
  
  bool Fraudeur=false;
  
  LOG_GENERAL("NumRoundsToWait: ");
  LOG_GENERAL(NumRoundsToWait);
  LOG_GENERAL("\n"); 
  LOG_GENERAL("JoueurRoi: ");
  LOG_GENERAL(JoueurRoi);
  LOG_GENERAL("\n"); 
  
  do
  {
    for (int i=0; i<nbj; i++)
    {
      bool CurrentState = ReadPlayerInput(i);

      if(CurrentState && !PreviousState[i] && i==JoueurRoi && !Fraudeur)
      {
        SelectedGameType++;
        if(SelectedGameType>MAX_GAMETYPE_ROI)
        {
          SelectedGameType=-1;
          TurnOffAllRedLights();
        }
        
        GameTypeSelLightOffCounter=RoundCounter+Delai_GameTypeSel;
        
        if(NumRoundsToWait-RoundCounter<40)
        {
          LOG_GENERAL("Rectification NumRoundsToWait\n");
          NumRoundsToWait=RoundCounter+40;
        }
        
        if(NumRoundsToWait<GameTypeSelLightOffCounter)
        {
          NumRoundsToWait+=random(PetitFraudeurExtraRoundsMin, PetitFraudeurExtraRoundsMax);
        }

        //Activate all lights that correspond to the selected mode.
        if(RoiLumiere)
        {
          for(int i=0; i<=SelectedGameType; i++)
          {
            ActivateRedLight(i);
          }
        }
        else(MoveDEDUFlag(SelectedGameType+1));
      }
      
      if (CurrentState && !PreviousState[i] && i!=JoueurRoi && !ReadPlayerOutput(i))
      {
        //Nouveau Fraudeur
        //Activate the output
        if(!Fraudeur) 
        {
          LOG_GENERAL("Premier Fraudeur\n");
          TurnOffAllRedLights();
          ExtraDelai=random(FraudeurExtraRoundsMin, FraudeurExtraRoundsMax);
          MoveDEDUFlag(random(25,60));
          tone(Tone_Pin, 1500, 200);
          LightOffCounter = RoundCounter+ExtraDelai;
        }
        else
        {
          ExtraDelai=random(PetitFraudeurExtraRoundsMin, PetitFraudeurExtraRoundsMax);
          LightOffCounter += ExtraDelai;
        }
        ActivateRedLight(i);
        MultGameProb(Game_id_ROI,1.05);
        
        LOG_GENERAL("Ajout Delai: ");
        LOG_GENERAL(ExtraDelai);
        LOG_GENERAL("\n");        
        
        if(NumRoundsToWait-RoundCounter<40)
        {
          LOG_GENERAL("Rectification NumRoundsToWait\n");
          NumRoundsToWait=RoundCounter+40;
        }
        NumRoundsToWait += ExtraDelai;
        
        Fraudeur=true;
      }
      PreviousState[i] = CurrentState;
    }
    
    if(!Fraudeur && RoundCounter>GameTypeSelLightOffCounter)
    {
      TurnOffAllRedLights();
    }

    if(RoundCounter > LightOffCounter && Fraudeur)
    {
      Fraudeur=false;
      TurnOffAllRedLights();
      MoveDEDUFlag(0);
      LOG_GENERAL("Retour à la normale\n");
      LOG_GENERAL("NumRoundsToWait: ");
      LOG_GENERAL(NumRoundsToWait);
      LOG_GENERAL("\n");
      LOG_GENERAL("RoundCounter: ");
      LOG_GENERAL(RoundCounter);
      LOG_GENERAL("\n");
    }
    
    //Internal delay
    delay(40);
    RoundCounter++;
  }while(RoundCounter<NumRoundsToWait);

  LOG_GENERAL("===============\n");
  LOG_GENERAL("FRAUDEURTERMINE\n");
  LOG_GENERAL("===============\n");
  
  if(!OverrideGameTypeFromFraudeur)
  {
    ExclusiveGameType=SelectedGameType!=-1;
    ExclusiveGameType_ID=SelectedGameType;
  }
  
  LOG_GENERAL("ExclusiveGameType: ");
  LOG_GENERAL(ExclusiveGameType);
  LOG_GENERAL("\n"); 
  LOG_GENERAL("ExclusiveGameType_ID: ");
  LOG_GENERAL(ExclusiveGameType_ID);
  LOG_GENERAL("\n"); 
}

#ifdef ENABLE_LOGGING
  #define LOG_PQP(a) LOG_GAME(Game_id_PQP,a)
#else
  #define LOG_PQP(a)
#endif
void PQP()
{
  int Winner=-1;
  int r=random(5);
  int r2=random(2,100);
  
  LOG_PQP("r:");
  LOG_PQP(r);
  LOG_PQP("\n");
  LOG_PQP("r2:");
  LOG_PQP(r2);
  LOG_PQP("\n");

  //Init lights as GREEN.
  //Random Low intensity green from time to time.
  if (r == 4) 
  {
    ActivateGreenLED(1);
  }
  else 
  {
    ActivateGreenLED(r2);
  }
  
  do 
  {
    Winner=FirstActive(nbj_raw);
  }while (Winner == -1);

  WinnerSoundAndLight(Winner);
  UpdateWinner(Winner);
  delay(200);
}

int MarqueurHonte(int iJoueurChanceux, int iSpinDelay)
{
  return LumiereHonte(iJoueurChanceux, iSpinDelay, true, false);
}

#ifdef ENABLE_LOGGING
  #define LOG_TROMPE(a) LOG_GAME(Game_id_TO,a)
#else
  #define LOG_TROMPE(a)
#endif
void TrompeOeil()
{
  LOG_TROMPE("TROMPE");
  LOG_TROMPE("\n");
  
  int NumActive=-1;
  int maxIter=random(2500,4500);
  int maxIter_Sheep=2500;
  int IterVert=random(30,35);
  bool SwitchColor=false;
  bool SwitchToRed=false;
  int ToRED=IterVert+50;
  int ProbVert=4;
  bool GreenFirst=(random(ProbVert)==0);
  
  LOG_TROMPE("Game_Mode:");
  LOG_TROMPE(Game_Mode);
  LOG_TROMPE("\n");
  LOG_TROMPE("GreenFirst:");
  LOG_TROMPE(GreenFirst);
  LOG_TROMPE("\n");
  LOG_TROMPE("maxIter:");
  LOG_TROMPE(maxIter);
  LOG_TROMPE("\n");  
  LOG_TROMPE("IterVert:");
  LOG_TROMPE(IterVert);
  LOG_TROMPE("\n");  
  
  int Looser=-1;

  //Initialize Loosers Array
  int Loosers[nbj];
  for (int i=0; i<=nbj_raw;i++)
  {
    Loosers[i]=0;
  }
  
  if (GreenFirst)
  {
    //Init lights as green!
    ActivateGreenLED(random(1,5));
  }
  else
  {
    //Init lights as red!
    TurnOnAllRedLights();
  }

  for (int i=0; i<=maxIter; i++)
  {

    if (!SwitchColor && i>IterVert && GreenFirst)
    {
      SwitchColor=true;
      ActivateGreenLED(0);
      LOG_TROMPE("SWITCHING OFF GREEN");
      LOG_TROMPE("\n");  
    }

    if (!SwitchToRed && i>ToRED && GreenFirst)
    {
      SwitchToRed=true;
      TurnOnAllRedLights();
      LOG_TROMPE("SWITCHING TO RED");
      LOG_TROMPE("\n");  
    }
    
    Looser=FirstActive(nbj_raw);
    if (Looser>= 0) 
    {
      TurnOffAllRedLights();
      ActivateGreenLED(0);
      tone(Tone_Pin, 1500, 200);
      ActivateRedLight(Looser);
      Loosers[Looser]=1;
      break;
    }
    delay(1);
  }

  if (Looser>= 0)
  {
    for (int j=0; j<=maxIter_Sheep; j++)
    {
      for (int i=0; i<=nbj_raw;i++)
      {
        if (ReadPlayerInput(i) && Loosers[i]==0)
        {
          Loosers[i]=1;
          ActivateRedLight(i);
          tone(Tone_Pin, 1500, 200);
        }
      }
      delay(1);
    }
  }

  //Game End
  TurnOffAllRedLights();
  delay(250);
}


//Dernier qui pèse
void DQP()
{
  int z;
  int Perdant=-1;

  //init lights as purple
  ActivateBlueLED(100);
  TurnOnAllRedLights();
  
  z=nbj;

  do
  {
    z=z-ReadInputDeactivateOutputIfActive(nbj_raw);
  }while (z!=1);
  Perdant=FirstActiveOutput(nbj_raw);

  TurnOffNonActivePlayerRedLights();
  
  SingleLooserSoundAndLight(Perdant);
  
  delay(500);
}

//Debut FFA
void FFA()
{
  float myRand1=random(280,400)/100;
  int myRand2=random(25,32);
  
  JoueChanson(0,myRand1,false, true);
  
  for (int e=1; e<=myRand2; e++) {

    MoveDEDUFlag(100-random(20));

    TurnOnAllRedLights();
    delay(60 + random(200));
    TurnOffAllRedLights();

    ActivateBlueLED(80);
    delay(60 + random(200));
    DeactivateBlueLED();

    ActivateGreenLED(80);
    delay(60 + random(200));
    DeactivateGreenLED();
  }


  DeactivateBlueLED();
  DeactivateGreenLED();
  TurnOffAllRedLights();
  MoveDEDUFlag(0);
  delay(500);
}
