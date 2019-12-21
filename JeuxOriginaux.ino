int CalculDelaiFraudeur(bool iNormalDelay)
{
  if(iNormalDelay)  return random(25,50) + (11 - vitesse) * random(100);
  else return random(25,50) + (11 - vitesse) * random(50);
}

void Delay_Fraudeur(int r)
{
  //Debut DELAY et TESTFRAUDEUR --------------------------------------
  //Délai entre les jeux.
  //Pendant ce temps, si un joueur appuie sur sa manette, sa lumière rouge allume.  Même chose pour les voisins.
  int LoopsToGo=20;
  bool TriggerEnd=false;
  int x=0;
  
  //r=Nombre de fois où la boucle fraudeur va s'exécuter avant de passer au répartiteur.
  for (int a=1; a<=r; a++)
  {
    if (ReadInputActivateOutput(nbj_raw))
    {
      TriggerEnd=true;
      x=1;
      //Play tone and raise flag.
      tone(Tone_Pin, 1500, 400);
      MoveDEDUFlag(25);
    }
    if (TriggerEnd == true)
    {
      TriggerEnd=false;
      a=r-LoopsToGo;
    }
    //Internal delay
    delay(40);
  }

  //Fraudeurs identifiés
  if (x>0)
  {
    delay(500);
    MoveDEDUFlag(0);
    delay(500);
    TurnOffAllLights();
    Delay_Fraudeur(CalculDelaiFraudeur(false));
  }

  //Inclure une logique pour looper plus efficacement dans delay_fraudeur.
  //Inclure une logique pour enregistrer les clic du roi.
  //Inclure une logique pour modifier ExclusiveGameType et ExclusiveGameTypeID
  
  return 0;
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
