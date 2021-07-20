#pragma once

#ifndef statement_H_INCLUDED
#define statement_H_INCLUDED

#include <stdbool.h>

// Ep0.c
int ptr(char fileNameAddress[]);
void directionValueInitialization(unsigned int x, unsigned int y);
void directionValueUpdate(void);
void diectionPrintf(void);
int directionControlCenter(int a, int b);
void fun();
int manualAttack();
int manualAttackSec();
int operatingCenter(void);
int game(char numID[2]);

// Main.c
int Menu(int Position, char MenuList[][16], bool Reset);
inline int __MenuOperate(int mode, int num, int Min, int Max);
inline int __MenuList(int mode, int num);

inline void SetMenuListMax(unsigned short int Number);
inline unsigned short int GetMenuListMax();
inline void SetMenuListMin(unsigned short int Number);
inline unsigned short int GetMenuListMin();

void getHelp(void);

// UserGroup.c
void SetSystem_User_VarNamePath(char* Message);
char* GetSystem_User_VarNamePath();
void SetSystem_User_VarName(char* Message);
char* GetSystem_User_VarName();
void SetSystem_Local_File_VarUserListPath(char* Message);
char* GetSystem_Local_File_VarUserListPath();
void SetSystem_Local_File_VarMainPath(char* Message);
char* GetSystem_Local_File_VarMainPath();
void SetSystem_User_VarAllUserNumber(unsigned short int Number);
unsigned short int GetSystem_User_VarAllUserNumber();
char* GetSystem_User_AllUserList_ToString(unsigned short int Index);
void SetSystem_User_Register(bool Active);
bool GetSystem_User_Register();

int aaa();
int Register();
int Login();

inline int __ReadLocalFile_UserList();
inline int __WriteLocalFile_UserList(char* Message);
inline void __Reset();

#endif
