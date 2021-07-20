#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#include "Declaration.h"
#include "Platform.Rmdust.Error.h"

static struct _User {
  struct _SystemUser {

    char* Name;
    char* NamePath;

    bool Online;
    bool Register;

    //char* AllUserList[128];
    char AllUserList[128][128];
    unsigned short int AllUserNumber;
  } User;

  struct _SystemLocal {

    struct _SystemLocalFile {
      bool Active;

      char* MainPath;
      char* UserListPath;



    } File;


  } Local;

} System;

void SetSystem_User_VarNamePath(char* Message) {
  System.User.NamePath = Message;
}
char* GetSystem_User_VarNamePath() {
  return System.User.NamePath;
}

void SetSystem_User_VarName(char* Message) {
  System.User.Name = Message;
}
char* GetSystem_User_VarName() {
  return System.User.Name;
}

void SetSystem_Local_File_VarUserListPath(char* Message) {
  System.Local.File.UserListPath = Message;
}
char* GetSystem_Local_File_VarUserListPath() {
  return System.Local.File.UserListPath;
}

void SetSystem_Local_File_VarMainPath(char* Message) {
  System.Local.File.MainPath = Message;
}
char* GetSystem_Local_File_VarMainPath() {
  return System.Local.File.MainPath;
}

void SetSystem_User_VarAllUserNumber(unsigned short int Number) {
  System.User.AllUserNumber = Number;
}
unsigned short int GetSystem_User_VarAllUserNumber() {
  return System.User.AllUserNumber;
}

char* GetSystem_User_AllUserList_ToString(unsigned short int Index) {
  return System.User.AllUserList[Index];
}

void SetSystem_User_Register(bool Active) {
  System.User.Register = Active;
}
bool GetSystem_User_Register() {
  return System.User.Register;
}


int Register() {
  // Write to local Userlist.txt
  __WriteLocalFile_UserList(GetSystem_User_VarName());
  return 1;
}

int Login() {
  System.User.Online = TRUE;

  return 1;
}

int aaa() {
  System.User.Online = FALSE;
  __Reset();

  if (!__ReadLocalFile_UserList()) {
    return 0;
  }

  char User[128 + 1] = {0};
  scanf_s("%s",&User,128);

  // Verify : User put in the user-Name
  for(unsigned short int Index = GetSystem_User_VarAllUserNumber();Index > 0;Index -= 1) {
    if (0 == strcmp(User,GetSystem_User_AllUserList_ToString(Index))) {
      SetSystem_User_Register(TRUE);
      break;
    }

    SetSystem_User_Register(FALSE);
  }
  SetSystem_User_VarName(User);

  if (!GetSystem_User_Register()) {
    Register(); 
  }
  Login();


  __Reset();

  return 1;
}

inline int __ReadLocalFile_UserList() {
  FILE* Path = NULL;
  fopen_s(&Path,GetSystem_Local_File_VarUserListPath(),"r+");

  if (Path == NULL) {
    return 0;
  }

  unsigned short int Index = 0;
  while(!feof(Path)) {
    fgets(System.User.AllUserList[Index],128,Path);
    Index += 1;
  }
  
  fclose(Path);
  
  System.User.AllUserList[Index][0] = '\0';

  SetSystem_User_VarAllUserNumber(Index - 1);

  return 1;
}

inline int __WriteLocalFile_UserList(char* Message) {
  FILE* Path = NULL;
  fopen_s(&Path,GetSystem_Local_File_VarUserListPath(),"a+");

  if (Path == NULL) {
    return 0;
  }

  fprintf(Path,"%s\n",Message);

  fclose(Path);

  return 1;
}

void __Reset() {
  // Var
  SetSystem_Local_File_VarMainPath("C:\\Users\\Public\\Documents\\RMDUST\\ShadowOfWorld\\");
  SetSystem_Local_File_VarUserListPath("C:\\Users\\Public\\Documents\\RMDUST\\ShadowOfWorld\\Save\\List.txt");

  if (System.User.Online) {
    // Alink both to name.
    char Path[256 + 1] = {0};
    strcat_s(Path,256,"C:\\Users\\Public\\Documents\\RMDUST\\ShadowOfWorld\\Save\\");
    strcat_s(Path,256,GetSystem_User_VarName());
    Rmdust_System_IO_Folder_Create(Path);

    strcat_s(Path,256,"\\Inf.txt");
    Rmdust_System_IO_File_Create(Path);
  }

  // Create Files
  Rmdust_System_IO_Folder_Create(GetSystem_Local_File_VarMainPath());
  Rmdust_System_IO_Folder_Create("C:\\Users\\Public\\Documents\\RMDUST\\ShadowOfWorld\\Save\\");
  Rmdust_System_IO_File_Create(GetSystem_Local_File_VarUserListPath());
}




