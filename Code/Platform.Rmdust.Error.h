
#pragma once

#ifndef _RMDUST_ERROR
#define _RMDUST_ERROR

#include <stdio.h>

#if _WIN32
void Rmdust_System_Console_Color_Update();
int Rmdust_Reset();
int Rmdust_System_Log_GetLableLevel();
char* Rmdust_System_Log_GetLableLevel_ToString();
void Rmdust_System_Log_SetLableLevel(int Number);

void Rmdust_System_Log_SetLogActive(bool Active);
bool Rmdust_System_Log_GetLogActive();
void Rmdust_System_Log_SetTitle(char* Message);
char* Rmdust_System_Log_GetTitle();
void Rmdust_System_Log_SetTitleAddons(char* Message);
char* Rmdust_System_Log_GetTitleAddons();
void Rmdust_System_Log_SetMessage(char* Message);
char* Rmdust_System_Log_GetMessage();
void Rmdust_System_Console_Graphic_Animation_BasicMessage(char* Message);
void Rmdust_System_Console_Graphic_Animation_LeaveMessage(char Message[]);
void Rmdust_System_Console_Graphic_Animation_Load();
inline void static __Print();
inline void static __Println();
inline void static __Printf();
void Rmdust_System_Console_Graphic_Text_Window(char* Message);
void Rmdust_System_Console_Graphic_Text_Window_SquareLine(char* Message);
int Rmdust_System_Console_Graphic_Text_Logo();
inline void static __SetPos(short int x, short int y);
int Rmdust_System_IO_Error_Log_Reset();
int Rmdust_System_IO_Error_Log_Write();
int Rmdust_System_IO_Folder_Create(char* FolderName);
int Rmdust_System_IO_File_Create(char* FileName);
#endif


#endif

