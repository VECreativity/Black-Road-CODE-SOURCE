#include "Declaration.h"

# include <stdio.h>
# include <conio.h>
# include <windows.h>
# include <stdbool.h>

struct direction {
  int x, y;
}old, neww;
struct active {
  int life, operation;
  int sys;
}set;

char worldArr[30][61];

int ptr(char fileNameAddress[]) {
  FILE *ptrAddress = NULL;
  fopen_s(&ptrAddress,fileNameAddress,"r");
  if (ptrAddress == NULL) {
    return 0;
  }

  int width = 0;
  while (!feof(ptrAddress)) {
    if (width == 30) {
      fclose(ptrAddress);
      return 0;
    }
    for (int count = 0; count < 60;count ++) {
      worldArr[width][count] = (char)fgetc(ptrAddress);
    }
    worldArr[width][60] = '\0';
    width++;
  }
  fclose(ptrAddress);
  return 0;
}

//  struct direction : old.x & old.y & neww.x & neww.y
void directionValueInitialization(unsigned int x, unsigned int y) {
  old.x = x;
  old.y = y;
  neww.x = old.x;
  neww.y = old.y;
  set.life = 100;
  set.operation = 100;
}
void directionValueUpdate(void) {
  if (old.x != neww.x || old.y != neww.y) {
    worldArr[old.y][old.x] = ' ';
    worldArr[neww.y][neww.x] = '#';
    old.y = neww.y;
    old.x = neww.x;
  }
}

void diectionPrintf(void) {
  system("cls");
  for (int count = 0; count < 30; count++) {
    printf("%s\n", worldArr[count]);
  }
  printf("LIFE : %d  |  OPERATION : %d" , set.life,set.operation);


}

int directionControlCenter(int a, int b) {
  if (a == 0 && b == 0) {
    return -1;
  }
  if (neww.y + 1 >= (int)sizeof(worldArr) || worldArr[neww.y + a][neww.x + b] != ' ') {
    return -1;
  }
  neww.y += a;
  neww.x += b;
  return 0;
}

int operatingCenter(void) {
  int valueOne = 0, valueTwo = 0, control = 0;
  bool jump = FALSE;
  
  switch (getch()) {
    //  Attack
    case 'e':manualAttack();break;
    //  Move : Foot
    case 'a':valueTwo = -1;break;
    case 'd':valueTwo = 1;break; 
    case 'w':valueOne = -1;control = 3;break;
    //  Move : Jump
    case ' ':
      switch (getch()) {
        case 'a':valueOne = -1;valueTwo = -1;break;
        case 'd':valueOne = -1;valueTwo = 1;break;
        case 'w':valueOne = 0;jump = TRUE;break;
      }
      control = 3;
      break;
    //  Ability
    case '-':set.sys = 0;return -1;break;
    case '=':set.sys = -1;return -1;break;
    default:return 0;break;
  }
  int count = 0;

  if (jump == TRUE) {
    fun();
  }

  do {
    directionControlCenter(valueOne , valueTwo);
    directionValueUpdate();
    diectionPrintf();
    Sleep(25);
    count ++;
  } while (count < control);
  do {
    manualAttackSec();
    directionValueUpdate();
    Sleep(25);
    diectionPrintf();
  } while (directionControlCenter(1, 0));

  return 0;
}

void fun() {
  neww.y--;
  for (int count = 3;count >= 0;count --) {
    if (worldArr[neww.y][neww.x - 1] == ' ' && worldArr[neww.y + 1][neww.x - 1] != ' ') {
      neww.x --;
      break;
    } else if (worldArr[neww.y][neww.x + 1] == ' ' && worldArr[neww.y + 1][neww.x + 1] != ' ') {
      neww.x ++;
      break;
    } else {
      directionControlCenter(-1,0);
      directionValueUpdate();
      Sleep(25);
      diectionPrintf();
    }
  }

}

int manualAttack() {
  if (worldArr[neww.y][neww.x - 1] == '!' || worldArr[neww.y][neww.x + 1] == '!') {
    worldArr[neww.y][neww.x - 1] = ' ';
    worldArr[neww.y][neww.x + 1] = ' ';
    return -1;
  }
  return 0;
}
int manualAttackSec() {
  if (worldArr[neww.y + 1][neww.x] == '!') {
    neww.y += 1;
    return -1;
  }
  return 0;
}

int game(char numID[2]) {
  
  switch(numID[0]) {
    case '0':
      switch(numID[1]){
        case '0':ptr("./resource/core/ptr/ptr00.txt");break;
        case '1':ptr("./resource/core/ptr/ptr01.txt");break;
      }

  }
  
  directionValueInitialization(0,0);
  diectionPrintf();
  //sendValueToDataFile(numID);

  while (operatingCenter()) {
  }

  if (set.sys == -1) {
    numID[1] ++;
    game(numID);
  }

  return 0;
}