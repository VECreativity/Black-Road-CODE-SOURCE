#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <malloc.h>
#include <Lmcons.h>

#include "Declaration.h"
#include "Platform.Rmdust.Error.h"

static struct _System {
  struct _SystemUser {
    char* Name;
    char WindowsUserPath[256 + 1];
    bool Online;
    bool Register;

    struct _SystemUserList {
      char Name[128 + 1];
      struct _SystemUserList* Next;
    } List;
    //char AllUserList[128][128];
    unsigned short int AllUserNumber;
  } User;

  struct _SystemLocal {
    struct _SystemLocalFile {
      bool Active;
    } File;
  } Local;

} System;

typedef struct _SystemUserList _SystemUserListNode, *UserListLinkList;
static UserListLinkList UserListHead;



int aaa() {

  // Init User's Online Activity.
  System.User.Online = FALSE;
  System.User.Register = FALSE;

  // Get Windows Local User Path.
  // __ReadLocalFile_UserList and _WriteLocalFile_UserList Need it.
  // InitLocalPath Need it.
  __LinkUserPath();

  // Init Local File.
  __InitLocalPath();


  // Init Var Value and Size , This is Link List.
  UserListHead = (UserListLinkList) malloc(sizeof(_SystemUserListNode));

  if (!UserListHead) {
    free(UserListHead);
    return 0;
  }
  UserListHead -> Next = NULL;

  // Read Local File ...\\Save\\List.txt
  if (!__ReadLocalFile_UserList()) {
    return 0;
  }

  char User[128 + 1] = {0};
  Set_SystemUserName(gets_s(User,128));

  // Verify "User" value is "Local File"'s One ?
  if (!__IsLocalFileUser()) {
    Set_SystemUserRegister(FALSE);
  } else {
    Set_SystemUserRegister(TRUE);
  }

  // If User is not lifeing.
  if (!Get_SystemUserRegister()) {
    // Create New Player.
    __Register(); 
  }

  __Login();


  __InitLocalPath();

  return 1;
}


inline static int __Register() {
  // Write to local Userlist.txt
  __WriteLocalFile_UserList(Get_SystemUserName());
  return 1;
}

inline static int __Login() {
  System.User.Online = TRUE;

  return 1;
}

inline static int __ReadLocalFile_UserList() {

  char Path[256 + 1] = {0};
  strcat_s(Path,256,Get_SystemUserWindowsUserPath());
  strcat_s(Path,256,"\\Documents\\Rmdust\\ShadowOfWorld\\Save\\List.txt");

  FILE* LocalPath = NULL;
  fopen_s(&LocalPath,Path,"r+");
  if (LocalPath == NULL) {
    return 0;
  }

  UserListLinkList Node = UserListHead , rear = UserListHead; 

  unsigned short int Index = 0;
  char temp[128 + 1] = {0}; 
  while(!feof(LocalPath)) {
    fgets(temp,128,LocalPath);

    if (strlen(temp) < 2) {
      break;
    }

    // Kill '\n'
    temp[strlen(temp) - 1] = '\0';


    Node = (UserListLinkList) malloc(sizeof(_SystemUserListNode));

    if (!Node) {
      free(Node);
      return 0;
    }

    strcpy_s(Node->Name,128,temp);

	  rear -> Next = Node;
	  rear = Node;
	  Node = Node -> Next;
    //__AddStringToLinkList(temp);

    Index += 1;
  }
  rear->Next=NULL;



  fclose(LocalPath);
  
  Set_SystemUserAllUserNumber(Index - 1);

  return 1;
}

inline static bool __IsLocalFileUser() {
  UserListLinkList Node = UserListHead -> Next ;

  for(unsigned short int Index = Get_SystemUserAllUserNumber();Index > 0;Index -= 1) {
    if (Node == NULL) {
      return FALSE;
    }
    
    if (0 == strcmp(Node->Name,Get_SystemUserName())) {
      return TRUE;
    }

    Node = Node->Next;
  }

  return FALSE;
}

// No use.
inline static int __AddStringToLinkList(char* Message) {
  UserListLinkList Node = UserListHead , rear = UserListHead; 

  Node = (UserListLinkList) malloc(sizeof(_SystemUserListNode));

  if (!Node) {
    free(Node);
    return 0;
  }

  strcpy_s(Node->Name,128,Message);

	rear -> Next = Node;
	rear = Node;
	Node = Node -> Next;

  return 1;
}

inline static int __WriteLocalFile_UserList(char* Message) {
  FILE* LocalPath = NULL;

  char Path[256 + 1] = {0};
  strcat_s(Path,256,Get_SystemUserWindowsUserPath());
  strcat_s(Path,256,"\\Documents\\Rmdust\\ShadowOfWorld\\Save\\List.txt");

  fopen_s(&LocalPath,Path,"a+");

  if (LocalPath == NULL) {
    return 0;
  }

  fprintf(LocalPath,"%s\n",Message);

  fclose(LocalPath);

  return 1;
}

inline static int __InitLocalPath() {

  char WindowsUserPath[256 + 1] = {0};
  strcat_s(WindowsUserPath,256,Get_SystemUserWindowsUserPath());
  const char* _Path = Get_SystemUserWindowsUserPath();

  // Create profiles for New player
  if (System.User.Online) {
    // C:\\User\\WindowsUserName\\Documents\\Rmdust\\ShaofWorld\\Save\\UserName
    strcat_s(WindowsUserPath,256,"\\Documents\\Rmdust\\ShadowOfWorld\\Save\\");
    strcat_s(WindowsUserPath,256,Get_SystemUserName());
    Rmdust_System_IO_Folder_Create(WindowsUserPath);

    // C:\\User\\WindowsUserName\\Documents\\Save\\UserName\\Inf.txt
    strcat_s(WindowsUserPath,256,"\\Inf.txt");
    Rmdust_System_IO_File_Create(WindowsUserPath);

    // Recovery.
    strcpy_s(WindowsUserPath,256,_Path);

    return 1;
  }

  strcat_s(WindowsUserPath,256,"\\Documents\\Rmdust\\ShadowOfWorld\\Save\\List.txt");
  Rmdust_System_IO_File_Create(WindowsUserPath);

  // Recovery.
  strcpy_s(WindowsUserPath,256,_Path);

  // Create Files
  FILE* LocalPath = NULL;
  fopen_s(&LocalPath,"./FileInfo.txt","r");

  if (LocalPath == NULL) {
    return 0;
  }


  char LocalMessage[256] = {0};
  while(!feof(LocalPath)){
    // 1. Use var WindowsUserPath's value to Create Folder.
    fgets(LocalMessage,128,LocalPath);

    // 2.1 First sysbol '*' mean It is description.
    if (LocalMessage[0] == '*') {
      continue;
    }

    // 2.2 First sysbol '\' mean Is is Past.
    if (LocalMessage[0] == '+') {
      break;
    }

    // 3. Yes, It is Past but we should Kill End sysbol '\n'.
    if (strlen(LocalMessage) > 1) {
      LocalMessage[strlen(LocalMessage) - 1] = '\0';
    }

    // 4. Link WindowUserPath and Path from FileInfo.txt.
    // C:\\Users\\WindowsUserName\\Decuments\\...
    strcat_s(WindowsUserPath,256,LocalMessage);

    // 5. Create Folder.
    Rmdust_System_IO_Folder_Create(WindowsUserPath);

    puts(WindowsUserPath);

    // 6. Recovery var WindowsUserPath's value from _Path.
    strcpy_s(WindowsUserPath,256,_Path);
  }
  strcpy_s(WindowsUserPath,256,_Path);


  fclose(LocalPath);

  return 1;
}

inline static char* __GetUserName() {
  
  
  return "Bre 97";
}

inline static void __LinkUserPath() {
  char Path[256 + 1] = {0};

  strcat_s(Path,256,"C:\\Users\\");
  strcat_s(Path,256,__GetUserName());

  strcpy_s(System.User.WindowsUserPath,256,Path);
}



///////////////////////////////////////////////////SetSystem_User_VarName///////////////////



void Set_SystemUserWindowsUserPath(char* Message) {
  strcpy_s(System.User.WindowsUserPath,128,Message);
}
char* Get_SystemUserWindowsUserPath() {
  return System.User.WindowsUserPath;
}

void Set_SystemUserName(char* Message) {
  System.User.Name = Message;
}
char* Get_SystemUserName() {
  return System.User.Name;
}

void Set_SystemUserAllUserNumber(unsigned short int Number) {
  System.User.AllUserNumber = Number;
}
unsigned short int Get_SystemUserAllUserNumber() {
  return System.User.AllUserNumber;
}



void Set_SystemUserRegister(bool Active) {
  System.User.Register = Active;
}
bool Get_SystemUserRegister() {
  return System.User.Register;
}

void Set_SystemUserOnline(bool Active) {
  System.User.Online = Active;
}

bool Get_SystemUserOnline() {
  return System.User.Online;
}