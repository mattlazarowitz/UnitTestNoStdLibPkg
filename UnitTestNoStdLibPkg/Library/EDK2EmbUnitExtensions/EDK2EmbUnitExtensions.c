/** @file

 MIT License

Copyright (c) 2016 Matthew Lazarowitz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#include <Uefi.h>
#include <Library/PrintLib.h>
#include <Library/embUnit/config.h>
#include <Library/embunit/AssertImpl.h>
#include <Library/UefiLib.h>

/**
  define stdimpl_print for embUnit. Done this way so the embUnit code can remain unchanged

  @param[in] string  The string to be output
**/
void stdimpl_print(const char *string){
  AsciiPrint(string);
}


/**
  This is an assert worker for embUnit designed to work with CHAR16 strings
  
  @param[in] ExpectedData  The expected string data as specified by the test.
  @param[in] ActualData    The actual data generated from the test.
  @param[in] LineNumber    The line number of the test assert.
  @param[in] FileName      The file name of of the test assert
  
**/
void assertImplementationC16Str(
  const CHAR16 *ExpectedData,
  const CHAR16 *ActualData, 
  UINT32 LineNumber, 
  const CHAR8 *FileName
  )
{
  CHAR8 buffer[ASSERT_STRING_BUFFER_MAX];

  //this line is slightly modified from the embUnit source to be a const int rather than a #define.
  //const UINTN ExpectedAssertBufferLimit = ((ASSERT_STRING_BUFFER_MAX-11-1)/2);//"exp'' was''" = 11 byte

  if (ExpectedData == 0) {
    ExpectedData = L"null";
  }

  if (ActualData == 0) {
    ActualData = L"null";
  }

  AsciiSPrint(buffer,ASSERT_STRING_BUFFER_MAX,"exp \"%S\" was \"%S\"",ExpectedData,ActualData);
  addFailure(buffer, LineNumber, FileName);
}

