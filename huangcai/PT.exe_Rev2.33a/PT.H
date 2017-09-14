// include the header file
#include <function.h>
#include <cmos.h>
#include <io.h>
#include <fcntl.h>
//#include <OBJDKEY.h>


#define ReadSize	10240
//#define Debug 		0
// declare the procedure name


void ReadMe(void);
void Logo(void);
void End(int ReturnCode);
void DecCmp(char *dwValue1,char *dwValue2);
void HexCmp(char *dwValue1,char *dwValue2);
int cXtoD(char T[],int num );
Boolean blWork(void);
uLong dwTransferNowDateTime2GMT(void);
uLong dwGetFileSize(char *fn);
void DisplayTxtFile(char *filename, int x, int y, uChar attr); // add at 2000-11-23, KC
void CP(char *fn1, char *fn2);
Boolean blFileCompare(char *fn1, char *fn2, Boolean blignore); // add at 2000-12-28, KC
Boolean blFileCheckSum(char *fn1, uInt wUserCheckSum);
Boolean Process_ini_File(int,int,int,char **,char *);
Boolean Process_ini_File2(int,int,char **);
Boolean CheckChar(char Filename[80],int ReadBit,char ch);
Boolean Transfer_Barcode_Format(char *);
Boolean Set_Barcode_Environment(char DataFilename[80],char iniFilename[80]);
Boolean Transfer_String(char File[50],char str1[50],char str2[50]);
Boolean GetString(char File1[50]);
Boolean Set_Environment_Variable(char str3[80],char EnvirVar[80],char In_File[20],char Out_File[20]);
Boolean WlFileIntoCertainPosition(char *fn1, char *fn2, char *fn3, char *place);//add at 2004-03-23, Yushih
Boolean blOBWSN(char *fn);
Boolean blCreateRandom(const uInt);
Boolean blDisplayBigWord(const char*);
int atoh(const char*);

Boolean blCheckLines (const char*);
Boolean blCmpData(char str[20],char file1[20],char file2[20]);
Boolean blCopyData(char sstr[50],char tstr[50],char s_File[20],char t_File[20]);
Boolean blTransferHex2Dec(char *file);
Boolean blCompareValueInFile(char *szFile, char *szValue);
Boolean blCompareValueInFile1(char *szFile, char *szValue);
Boolean blCheckString(char *szFile, char *szValue);
void DCF(char *dwValue1,char *dwValue2);
void HCF(char *dwValue1,char *dwValue2);