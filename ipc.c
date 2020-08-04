#include "main.h"

#ifdef WINWIN_BUILD

void WriteToPipe(char* s, struct player *p)

// Read from a file and write its contents to the pipe for the child's STDIN.
// Stop when there is no more data.
{
printf("%s",s);
   DWORD dwRead, dwWritten;
   dwRead=strlen(s);
   CHAR chBuf[BUFSIZE];
   strncpy(chBuf,s,dwRead);
   BOOL bSuccess = FALSE;

   /*for (;;)
   {
      bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL);
      if ( ! bSuccess || dwRead == 0 ) break;

      bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL);
      if ( ! bSuccess ) break;
   }*/

   bSuccess = WriteFile(p->g_hChildStd_IN_Wr, s, dwRead, &dwWritten, NULL);
   if ( ! bSuccess )ErrorExit(TEXT("StdInWr unsuccesful"));
   //Sleep(10);

// Close the pipe handle so the child process stops reading.

  /* if ( ! CloseHandle(g_hChildStd_IN_Wr) )
      ErrorExit(TEXT("StdInWr CloseHandle"));*/
}

void ReadFromPipe(struct player *p, char* mr) //signal if message from engine is cut in 2 (missing the \n), should not happen

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT.
{
   DWORD dwRead, dwWritten;
   CHAR chBuf[BUFSIZE+1];
   chBuf[BUFSIZE]=0;
   BOOL bSuccess = FALSE;
   HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   //Sleep(1000);
   DWORD dwERR;
bSuccess = ReadFile( p->g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, &p->OV);



if(!bSuccess){for(;;)
    {DWORD res=0;res=GetOverlappedResult(p->g_hChildStd_OUT_Rd,&p->OV,&dwRead,FALSE);
if(!res){
dwERR=GetLastError();
if(dwERR== ERROR_HANDLE_EOF)break;
if(dwERR== ERROR_IO_INCOMPLETE)
  ; // Sleep(1);
}else break;}
}
//DWORD res=0;if( ! bSuccess)res=GetOverlappedResult(g_hChildStd_OUT_Rd,&OVVV,&dwRead,FALSE);
/*//SetLastError(0);
if( ! bSuccess){DWORD dwERR=GetLastError();
if(dwERR== ERROR_HANDLE_EOF)break;
    //{Sleep(100);continue;}
    {res=GetOverlappedResult(g_hChildStd_OUT_Rd,&OVVV,&dwRead,FALSE);
    }
else ErrorExit(TEXT("Readfile error"));}
*/

/*if(!GetOverlappedResultEx(g_hChildStd_OUT_Rd,&OVVV,&dwRead,1000,FALSE)||!bSuccess)
    {DWORD dwERR=GetLastError();
if(dwERR==WAIT_TIMEOUT)ErrorExit(TEXT("GetOverlappedResultEx timeout"));}
if( ! bSuccess || dwRead == 0 )
        break;*/
      /*DWORD res=0;res=   WaitForSingleObject(hEvent,2000);
    if(res)ErrorExit(TEXT("WaitForSingleObject hEvent"));*/
      bSuccess = WriteFile(hParentStdOut, chBuf,
                           dwRead, &dwWritten, NULL);
     // if (! bSuccess ) break;
     if(mr)
     strncpy(mr,chBuf,dwRead);

}


#endif // WINWIN_BUILD
