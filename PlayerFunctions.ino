void AllocateTwoTeams(int NbjToAllocate)
{
  int NbjAlloueEq1=0;
  int NbjAlloueEq2=0;

  //Reset Array
  for (int i=0; i<nbj_max; i++)
  {
    Equipes[i]=-1;
  }
  
  NbEquipes=2;
  if (NbjToAllocate%2==0)
  {
    NbJoueursEq1=NbjToAllocate/2;
    NbJoueursEq2=NbJoueursEq1;
  }
  else
  {
    if (random(2)==0)
    {
      NbJoueursEq1=(NbjToAllocate+1)/2;
      NbJoueursEq2=NbjToAllocate-NbJoueursEq1;
    }
    else
    {
      NbJoueursEq1=(NbjToAllocate-1)/2;
      NbJoueursEq2=NbjToAllocate-NbJoueursEq1;
    }
  }

  for (int i=0; i<NbjToAllocate; i++)
  {
    if (random(2)==0 && NbjAlloueEq1<NbJoueursEq1)
    {
      Equipes[i]=0;
      NbjAlloueEq1++;
    }
    else if (NbjAlloueEq2<NbJoueursEq2)
    {
      Equipes[i]=1;
      NbjAlloueEq2++;
    }
    else
    {
      Equipes[i]=0;
      NbjAlloueEq1++;
    }
  }
  
  LOG_GENERAL("NbjToAllocate: ");
  LOG_GENERAL(NbjToAllocate);
  LOG_GENERAL("\nAssignations des équipes\n");
  for (int i=0; i<NbjToAllocate; i++)
  {
    LOG_GENERAL("ID: ");
    LOG_GENERAL(i+1);
    LOG_GENERAL("  Eq: ");
    LOG_GENERAL(Equipes[i]);
    LOG_GENERAL("\n");
  }
  LOG_GENERAL("=====\n");
}

void AllocateTwoConsecutiveTeams()
{
  //init at -1
  for (int i=0; i<=nbj_raw_max; i++)
  {
    Equipes[i]=-1;
  }
  
  NbEquipes=2;
  if (nbj%2==0)
  {
    NbJoueursEq1=nbj/2;
    NbJoueursEq2=NbJoueursEq1;
  }
  else
  {
    if (random(2)==0)
    {
      NbJoueursEq1=(nbj+1)/2;
      NbJoueursEq2=nbj-NbJoueursEq1;
    }
    else
    {
      NbJoueursEq1=(nbj-1)/2;
      NbJoueursEq2=nbj-NbJoueursEq1;
    }
  }
  LOG_GENERAL("NbJoueursEq1:");
  LOG_GENERAL(NbJoueursEq1);
  LOG_GENERAL("\n");
  LOG_GENERAL("NbJoueursEq2:");
  LOG_GENERAL(NbJoueursEq2);
  LOG_GENERAL("\n");
  
  for (int i=0; i<=nbj_raw; i++)
  {
    if (i<NbJoueursEq1)
    {
      Equipes[i]=0;
    }
    else
    {
      Equipes[i]=1;
    }
  }

  for (int i=0; i<=nbj_raw_max; i++)
  {
    LOG_GENERAL(Equipes[i]);
    LOG_GENERAL("\n");
  }
}

void DefinirOrdreJoueurs(int equipe,int NombreActions)
{
  int JoueurPrec=0;
  //Reset
  for (int i=0; i<NbNoteMax; i++)
  {
    OrdreJoueurs[i]=-1;
  }
  
  for (int i=0; i<NombreActions; i++)
  {
    for (int j=JoueurPrec;j<=nbj_raw;j++)
    {
      if (Equipes[j]==equipe)
      {
        OrdreJoueurs[i]=j;
        
        if (j==nbj_raw)
        {
          JoueurPrec=0;
        }
        else
        {
          JoueurPrec=j+1;
        }
        break;
      }
      if (j==nbj_raw)
      {
        j=-1;
      }
    }
  }
}

int ProchainJoueur(int iJoueurActuel,int iNombrePlaces,int iDirection)
{
  int wProchain=-1;
  int wNombrePlaces=iNombrePlaces%nbj_raw;
  
  //Protection
  if ((iDirection == 1 || iDirection == -1) && (iJoueurActuel>=0 && iJoueurActuel<=nbj_raw))
  {
    wProchain=iJoueurActuel + wNombrePlaces * iDirection;
    
    //Wrap-Around?
    if (wProchain<0)
    {
      wProchain=nbj_raw + wProchain+1;
    }
    else if (wProchain>nbj_raw)
    {
      wProchain=wProchain - nbj_raw-1;
    }
    
    return wProchain;
  }
  else
  {
    return -1;
  }
}

int WrapAround(int iPlayer)
{
  int wPlayer=iPlayer;
  if (wPlayer>nbj_raw)
  {
    wPlayer=0;
  }
  else if (wPlayer<0)
  {
    wPlayer=nbj_raw;
  }
  return wPlayer;
}

int NextPlayerInTeam(int CurrentPlayer,int iTeam,int iDirection)
{
  int Player;
  for (int i=1; i<nbj; i++)
  {
    Player=CurrentPlayer+iDirection*i;
    
    if (Player>=nbj)
    {
      Player-=nbj;
    }
    else if (Player<0)
    {
      Player+=nbj;
    }

    if (Equipes[Player]==iTeam)
    {
      return Player;
    }
  }
  return -1;
}

int CountActivePlayers(bool PlayersInGame[], int NbPlayers)
{
  int ActivePlayers=0;
  for (int i=0; i<NbPlayers; i++)
  {
    if (PlayersInGame[i]) 
    {
      ActivePlayers++;
    }
  }
  return ActivePlayers;
}

