#include "Declaration.h"
#include "Other.Platform.H.vec.Description.h"
#include "Platform.Rmdust.Error.h"

#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>



int main(void) {

  Rmdust_Reset();

  Rmdust_System_Log_SetTitle("Start Core");
  Rmdust_System_Log_SetTitleAddons("Non");
  Rmdust_System_Log_SetLableLevel(2);
  Rmdust_System_Log_SetLogActive(TRUE);
  Rmdust_System_IO_Error_Log_Write();

  aaa();

  system("pause");

  //char arr[][16] = { "Game Start", "Game Passage", "Help", "Back User","Game Exit","\0" };
  //Menu(0,arr,TRUE);


  return 0;
}



static struct System {
  struct SystemMenu {
    unsigned short int LineMax;
    unsigned short int LineMin;
  } Menu;

} System;

inline void SetMenuListMax(unsigned short int Number) { System.Menu.LineMax = Number; }
inline unsigned short int GetMenuListMax() { return System.Menu.LineMax; }
inline void SetMenuListMin(unsigned short int Number) { System.Menu.LineMin = Number; }
inline unsigned short int GetMenuListMin() { return System.Menu.LineMin; }


int Menu(int Position, char MenuList[][16],bool Reset) {
  // First put in 0.
  if (Position < 0) {
    return 0;
  }

  // Get size for MenuList the min and max.
  if (Reset) {
    for (unsigned short int OutIndex = 0; 1; OutIndex += 1) {
      SetMenuListMax(OutIndex - 1);

      if (MenuList[OutIndex][0] == '\0') {
        break;
      }

      for (unsigned short int InIndex = 0; 1; InIndex += 1) {
        if (MenuList[OutIndex][InIndex] == '\0') {
          break;
        }
      }
    }

    SetMenuListMin(0);
  }


  system("cls");

  for (unsigned short int in = 0; in < GetMenuListMax();in += 1) {
    printf("%s\n",MenuList[in]);
  }
  printf("%s\n",MenuList[Position]);


  Menu(__MenuOperate(1, Position, GetMenuListMin(), GetMenuListMax()),MenuList,FALSE);

  return 0;
} 
inline int __MenuOperate(int mode, int num, int Min, int Max) {
  switch (getch()) {
  case 119:
    if (num != Min) {
      num--;
    }
    break;
  case 115:
    if (num != Max) {
      num++;
    }
    break;
  case 13:
    if (__MenuList(mode, num) == -1) {
      return -1;
    }
    break;
  }

  return num;
}
inline int __MenuList(int Mode, int OperationType) {

  switch (Mode) {
    
      
    // Main-Menu
    case 1:
      switch (OperationType) {
        case 0:
          
          break;
        case 1:
          
          break;
        case 2:
          getHelp();
          break;
        case 3:
          
          break;
        case 4:
          return -1;
          break;
      }
      break;
  }

  return 1;
}

void getHelp(void) {
  system("cls");
  Rmdust_System_Console_Graphic_Text_Window_SquareLine("1234567");
  system("pause");
}
