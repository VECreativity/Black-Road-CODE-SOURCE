



#include <direct.h>
#include <io.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "Platform.Rmdust.Error.h"

// New
#define AND &&
#define OR ||
#define and &&
#define or ||
#define Graphic_Animation_Transition_Time 50

static char __Text = '=';
static char __Space = ' ';
static unsigned short int __WindowsHeight = 40;
static unsigned short int __WindowsWidth = 120;

static unsigned short int __WindowWidthCenter = 60;
static unsigned short int __WindowWidthEnd = 57;


static struct System {
  // Of Console ColorCode 
  struct SystemConsole {
    struct SystemConsoleColor {
      enum SystemConsoleColorList {
        Black,
        Blue,
        Green,
        GrayBlue,
        Red,
        Purple,
        GrayYellow,
        GrayWhite,
        GrayBlack,
        LightBlue,
        LightGreen,
        LightGrayBlue,
        LightRed,
        LightPurple,
        LightYellow,
        White
      } Background,Foreground;

      // Console-Color need this
      // Rmdust_System_Console_Color_Update() Use this


    } Color;

  } Console;

  // Of Logs
  struct SystemLog {
    char* Title;
    char* TitleAddons;
    char* Message;

    bool Active;

    enum SystemLogLableList {
      Error,
      Warning,
      Non 
    } Lable;

    int MessageIndex;

  } Log;

} System;


// Use this Before : Change struct -> System.Console.Color.Background
//                                    System.Console.Color.Foreground



// Initialize
// Should use this in first
int Rmdust_Reset() {
  
  system("color F0");
  system("mode con cols=120 lines=30");


  Rmdust_System_IO_Folder_Create("C:\\Users\\Public\\Documents\\RMDUST");
  
  Rmdust_System_Log_SetLogActive(false);
  System.Log.Lable = Non;
  Rmdust_System_IO_Error_Log_Reset();

  return 1;
}


void Rmdust_System_Console_Color_Update() {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(handle,(WORD)System.Console.Color.Foreground + (WORD)System.Console.Color.Background * 0x10);
}

// Lable
/*
 * 0 : Error
 * 1 : Warning
 * 2 : Non
 */
int Rmdust_System_Log_GetLableLevel() { 
  return System.Log.Lable;
}
char* Rmdust_System_Log_GetLableLevel_ToString() {
  switch (Rmdust_System_Log_GetLableLevel()) { 
    case 0:
      return "Error";
      break;
    case 1:
      return "Warning";
      break;
    case 2:
      return "Non";
      break;
    default:
      return "null";
  }
}

void Rmdust_System_Log_SetLableLevel(int Number) { System.Log.Lable = Number; }


// Write logs's Activity  status
void Rmdust_System_Log_SetLogActive(bool Active) { 
  System.Log.Active = Active;
}
bool Rmdust_System_Log_GetLogActive() { 
  return System.Log.Active; 
}

// Logs Information
/*
 * -;Title-|
 * TitleAddons
 * Message
 * -;
 */
void Rmdust_System_Log_SetTitle(char* Message) {
  System.Log.Title = Message;
}
char* Rmdust_System_Log_GetTitle() { 
  return System.Log.Title; 
}
void Rmdust_System_Log_SetTitleAddons(char* Message) {
  System.Log.TitleAddons = Message;
}
char* Rmdust_System_Log_GetTitleAddons() {
  return System.Log.TitleAddons;
}
void Rmdust_System_Log_SetMessage(char* Message) {
  System.Log.Message = Message;
}
char* Rmdust_System_Log_GetMessage() {
  return System.Log.Message;
}


// It printf to end 
void Rmdust_System_Console_Graphic_Animation_BasicMessage(char* Message) {
  size_t MessageLength = strlen(Message);

  for (size_t Index = 0;Index < MessageLength;Index += 1) {
    Sleep(Graphic_Animation_Transition_Time);
    printf("%c", *(Message + Index));
  }
}

// It printf to end and leave screeen
void Rmdust_System_Console_Graphic_Animation_LeaveMessage(char Message[]) {
  size_t MessageLength = strlen(Message);
  
  system("cls");
  Rmdust_System_Console_Graphic_Animation_BasicMessage(Message);

  // This Use 
  for (size_t Index = 0;Index < MessageLength;Index += 1) {
    size_t MessageIndexTemp = Index;


    system("cls");
    for (size_t InternalIndex = 0;InternalIndex < MessageLength;InternalIndex += 1) {
      if (Message[Index] < Message[InternalIndex]) {
        MessageIndexTemp = InternalIndex;
      }
    }

    if (MessageIndexTemp != Index) {
      Message[MessageIndexTemp] = ' ';
    }

    printf("%s", Message);
    Sleep(Graphic_Animation_Transition_Time);
  }
}

void Rmdust_System_Console_Graphic_Animation_Load() {
  for (int Count = 5;Count > 0;Count--) {
    __SetPos(60,20);
    printf("|");
    Sleep(100);

    __SetPos(60,20);
    printf("/");
    Sleep(100);

    __SetPos(60,20);
    printf("-");
    Sleep(200);

    __SetPos(60,20);
    printf("\\");
    Sleep(100);
  }
}


inline void static __Print() {
  for (unsigned short int Count = __WindowsWidth - 1;Count > 0 ;Count -= 1) {
    printf("%c" , __Text);
  }
}
inline void static __Println() {
  __Print();
  printf("\n");
}
inline void static __Printf() {
  printf("\n");
  __Print();
}

// Text Window
void Rmdust_System_Console_Graphic_Text_Window(char* Message) {
  __Println();
  printf("%s" , Message);
  __Printf();
}

// Text Window
// Support English/Chinese/Number In Windows 7
//         English/       /Number In Windows 10
void Rmdust_System_Console_Graphic_Text_Window_SquareLine(char* Message) {
  size_t MessageLength = strlen(Message);

  __Println();
  printf("%c" , __Text);
  for (size_t Count = __WindowWidthCenter - MessageLength/2;Count > 0;Count -= 1) {
    printf("%c" , __Space);
  }
  
  printf("%s" , Message);
  for (size_t Count = __WindowWidthEnd - 1 - (MessageLength % 2 == 0 ? MessageLength / 2 - 1 : MessageLength / 2);Count > 0 ;Count -= 1) {
    printf("%c" , __Space);
  }
  printf("%c" , __Text);
  __Printf();
}

// I use mine when I Start Console
// It read local file to Display to screen
int Rmdust_System_Console_Graphic_Text_Logo() {
  FILE* LocalPath = NULL;
  fopen_s(&LocalPath,"Resource/Logo.txt","r");

  if (LocalPath == NULL) {
    return 0;
  }

  while(!feof(LocalPath)){
    printf("%c",(char)fgetc(LocalPath));
  }
  
  return 1;
}

// Console pos direction
inline void static __SetPos(short int x, short int y) {
  COORD point = {
    x , y 
  };
    
  HANDLE HOutput = GetStdHandle( STD_OUTPUT_HANDLE );
  SetConsoleCursorPosition(HOutput, point);
}


// Use this when I start program
int Rmdust_System_IO_Error_Log_Reset() {
  FILE* FilePath = NULL;
  fopen_s(&FilePath, "C:\\Users\\Public\\Documents\\RMDUST\\Log.txt", "w+");

  if (FilePath == NULL) {
    return -1;
  }

  fclose(FilePath);

  return 1;
}


int Rmdust_System_IO_Error_Log_Write() {
  if (!Rmdust_System_Log_GetLogActive()) {
    return 0;
  }

  FILE* FilePath = NULL;
  fopen_s(&FilePath, "C:\\Users\\Public\\Documents\\RMDUST\\Log.txt", "a+");

  if (FilePath == NULL) {
    return 0;
  }

  fprintf(FilePath, "-;\n-%d%s\n-5%s\n%s\n%s\n-;\n\n",
          Rmdust_System_Log_GetLableLevel(),
          Rmdust_System_Log_GetLableLevel_ToString(),
          Rmdust_System_Log_GetTitle(),
          Rmdust_System_Log_GetTitleAddons(),
          Rmdust_System_Log_GetMessage());

  fclose(FilePath);

  Rmdust_System_Log_SetLogActive(false);

  return 1;
}


int Rmdust_System_IO_Folder_Create(char* FolderName) {
  if (!_access(FolderName, 0)) {
    return 0;
  }

  return _mkdir(FolderName);
}

int Rmdust_System_IO_File_Create(char* FileName) {
  FILE* Path = NULL;
  fopen_s(&Path,FileName,"a+");

  if (Path == NULL) {
    return 0;
  }

  fclose(Path);

  return 1;
}





/*
int _System_Time_GetDay() {
  time_t systemTime;
  struct tm *systemTimeAddress;
  time(&systemTime);
  gmtime_s(&systemTime, systemTimeAddress);
  return systemTimeAddress->tm_mday;
}
int _System_Time_GetMonth() {
  time_t systemTime;
  struct tm *systemTimeAddress;
  time(&systemTime);
  gmtime_s(&systemTime, systemTimeAddress);
  return systemTimeAddress->tm_mon;
}
*/

/*
 *  Writer : Bre 97
 *    Writer Information :
 *      Twitter-ID :     @Bre97_web
 *      Google-Mail :    BY.SGATN3@Gmail.com
 *      Outlook-Mail :   BY_SGATN3@Outlook.com
 *      GitHub-Name :    Bre97-web
 *    Writer Words :
 *      My Information is above this.
 *      You can give me with "Error Report"as I will Carefully.
 *      You can Upgrade this File,but you should have told me.
 *  About :
 *    Last Update date : 6.28.2021
 */
