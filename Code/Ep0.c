
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <process.h>

#include "Declaration.h"



struct _System {

  struct _SystemDirection {
    
    struct _SystemDirectionPods {
      int X, Y;

      struct _SystemDirectionPodsLast {
        int X, Y;
      } Last;
    } Pods;
  
    struct _SystemDirectionChange {
      int X, Y;
      char In;
    } Change;

  } Direction;

} System;

char maps[4][100] =  {
  "                               ",
  "                               ",
  "  #                            ",
  "=============  ================"
};

bool ac = false;
HANDLE _GetIn;
HANDLE _MapsUpdate;
HANDLE _MapsPut;

DWORD WINAPI __GetIn() {

  while(true) {
    
    System.Direction.Change.In = (char)_getch();

    switch(System.Direction.Change.In) { 
      case '=':
        CloseHandle(_GetIn);
        CloseHandle(_MapsUpdate);
        CloseHandle(_MapsPut);
        return 1;
      case 'w':System.Direction.Change.Y += 1;break;
      case 's':break;
      case 'a':System.Direction.Change.X -= 1;break;
      case 'd':System.Direction.Change.X += 1;
      default:
        break;
    }

    ac = false;

  }

  return 1;
}


DWORD WINAPI __MapsUpdate() {

  while(true) {
  
    while(ac){
    }
  
    if(maps[System.Direction.Pods.Y][System.Direction.Pods.X + System.Direction.Change.X] == ' ') {
      
      System.Direction.Pods.Last.Y = System.Direction.Pods.Y;
      System.Direction.Pods.Last.X = System.Direction.Pods.X;
      
      System.Direction.Pods.Y += System.Direction.Change.Y;
      System.Direction.Pods.X += System.Direction.Change.X;
      
    }


    // Kill System.Direction.Change...'s Value.
    // Important !!!
    System.Direction.Change.X = 0;
    System.Direction.Change.Y = 0;

    if(System.Direction.Pods.Last.X != System.Direction.Pods.X) {
      maps[System.Direction.Pods.Last.Y][System.Direction.Pods.Last.X] = ' ';
      maps[System.Direction.Pods.Y][System.Direction.Pods.X] = '#';
    }
    
    ac = true;
  }

  return 1;
}

DWORD WINAPI __MapsPut() {
  
  while(true) {
    puts(maps[0]);
    puts(maps[1]);
    puts(maps[2]);
    puts(maps[3]);
    
    system("cls");
  }

  return 1;
}




void Init() {
  System.Direction.Pods.X = 2;
  System.Direction.Pods.Y = 2;
  System.Direction.Change.In = 'v';
  System.Direction.Change.X = 0;
  System.Direction.Change.Y = 0;
}



int a() {

  Init();

  LPVOID _Thread = (LPVOID)10;

  _GetIn = CreateThread(NULL,0,__GetIn,_Thread,0,NULL);
  _MapsUpdate = CreateThread(NULL,0,__MapsUpdate,_Thread,0,NULL);
  _MapsPut = CreateThread(NULL,0,__MapsPut,_Thread,0,NULL);
  
  Sleep(10000);
  


  return 1;
}