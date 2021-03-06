void BesoinOrdreChansons(int c)
{
  LOG_GENERAL("C:");
  LOG_GENERAL(c);
  LOG_GENERAL("\n");
  if (c==0)
  {
    DefinirOrdreChansons();
  }
}
void DefinirOrdreChansons()
{
  bool NotGood=false;
  
  LOG_GENERAL("ORDRE");
  LOG_GENERAL("\n");
  for (int i=0;i<NombreChansons;i++)
  {
    do
    {
      NotGood=false;
      OrdreChansons[i]=random(NombreChansons);
      if (i==0)
      {
        if (OrdreChansons[i]==OrdreChansons[NombreChansons-1])
        {
          NotGood=true;
        }
      }
      else
      {
        for (int j=0; j<i; j++)
        {
          if (OrdreChansons[i]==OrdreChansons[j])
          {
            NotGood=true;
            break;
          }
        }
      }
    }while(NotGood);
    LOG_GENERAL("i:");
    LOG_GENERAL(i);
    LOG_GENERAL(" OrdreChansons:");
    LOG_GENERAL(OrdreChansons[i]);
    LOG_GENERAL("\n");
  }
  LOG_GENERAL("\n");
}

void JoueChanson(int Chanson, float FacteurVitesse, bool RandVitesse, bool Lumiere)
{
  int NombreNotes=SelectionChanson(Chanson);
  int myRand;
  float FactVit=FacteurVitesse;



  LOG_GENERAL("===============\n");
  LOG_GENERAL("= JoueChanson =\n");
  LOG_GENERAL("===============\n");
  
  LOG_GENERAL("NombreNotes:");
  LOG_GENERAL(NombreNotes);
  LOG_GENERAL("\n");
  LOG_GENERAL("RandVitesse:");
  LOG_GENERAL(RandVitesse);
  LOG_GENERAL("\n");

  if (RandVitesse)
  {
    myRand= random(ChansonFacteurRandomMin,ChansonFacteurRandomMax);
    FactVit=(float) myRand/100;
  }
  
  
  LOG_GENERAL("FactVit:");
  LOG_GENERAL(FactVit);
  LOG_GENERAL("\n");
  
  for (int n=0; n<NombreNotes; n++)
  {
    if (Lumiere)
    {
      switch(n%3)
      {
        case 0:
            TurnOnAllRedLights();
            break;
        case 1:
            ActivateBlueLED(80);
            break;
        case 2:
            ActivateGreenLED(80);
            break;
      }
    }
    //PlayNote(int Tone_Pin, float Freq, float PlayTime, float WaitTime)
    PlayNote(MaChanson[0][n], MaChanson[1][n]/FactVit, MaChanson[2][n]/FactVit);

    if (Lumiere) TurnOffAllLights();
  }

  LOG_GENERAL("===================\n");
  LOG_GENERAL("= JoueChanson FIN =\n");
  LOG_GENERAL("===================\n");
}

//Returns the number of notes.
int SelectionChanson(int Numero)
{
  float *pf;
  
  int NombreDeNotes;
  switch(Numero)
  {
    case 0:
      pf=(float *)ChansonDEDU;
      NombreDeNotes=sizeof(ChansonDEDU[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
        for (int j=0; j<NombreDeNotes;j++)
        {
          MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
        }
      }
      ChansonFacteurRandomMin=130;
      ChansonFacteurRandomMax=250;
      return NombreDeNotes;
    case 1:
      pf=(float*)ctd1;
      NombreDeNotes=sizeof(ctd1[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=105;
      ChansonFacteurRandomMax=155;
      return NombreDeNotes;
    case 2:
      pf=(float*)ctd2;
      NombreDeNotes=sizeof(ctd2[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=100;
      ChansonFacteurRandomMax=155;
      return NombreDeNotes;
    case 3:
      pf=(float *)Menuet;
      NombreDeNotes=sizeof(Menuet[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=80;
      ChansonFacteurRandomMax=135;
      return NombreDeNotes;
    case 4:
      pf=(float*)SWTheme;
      NombreDeNotes=sizeof(SWTheme[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=90;
      ChansonFacteurRandomMax=140;
      return NombreDeNotes;
    case 5:
      pf=(float*)Cantina;
      NombreDeNotes=sizeof(Cantina[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=85;
      ChansonFacteurRandomMax=115;
      return NombreDeNotes;
    case 6:
      pf=(float*)Scatman2;
      NombreDeNotes=sizeof(Scatman2[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=85;
      ChansonFacteurRandomMax=105;
      return NombreDeNotes;
    case 7:
      pf=(float*)Boten2;
      NombreDeNotes=sizeof(Boten2[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=100;
      ChansonFacteurRandomMax=150;
      return NombreDeNotes;
    case 8:
      pf=(float *)FurElise;
      NombreDeNotes=sizeof(FurElise[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=80;
      ChansonFacteurRandomMax=130;
      return NombreDeNotes;
    case 9:
      pf=(float *)FF6Over;
      NombreDeNotes=sizeof(FF6Over[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
          for (int j=0; j<NombreDeNotes; j++)
          {
              MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin=130;
      ChansonFacteurRandomMax=180;
      return NombreDeNotes;
    case 10:
      pf=(float*)Tetris;
      NombreDeNotes=sizeof(Tetris[0])/sizeof(float);
      for (int i=0; i<ParamChansons; i++)
      {
        for (int j=0; j<NombreDeNotes; j++)
        {
          MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
        }
      }
      ChansonFacteurRandomMin=115;
      ChansonFacteurRandomMax=160;
      return NombreDeNotes;
    //Max pour JeuChanson - Les tounes ci-bas ne peuvent jouer.
    case 11:
      pf = (float*)Figaro;
      NombreDeNotes = sizeof(Figaro[0]) / sizeof(float);      
      

      for (int i = 0; i < ParamChansons; i++)
      {
        for (int j = 0; j < NombreDeNotes; j++)
        {
          MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
        }
      }
      ChansonFacteurRandomMin = 125;
      ChansonFacteurRandomMax = 180;
      return NombreDeNotes;
    case 12:
      pf = (float*)FF3Win;
      NombreDeNotes = sizeof(FF3Win[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin = 200;
      ChansonFacteurRandomMax = 200;
      return NombreDeNotes;
    default:
      pf = (float*)CAN;
      NombreDeNotes = sizeof(CAN[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      ChansonFacteurRandomMin = 300;
      ChansonFacteurRandomMax = 300;
      return NombreDeNotes;

  }
}







