/*
     MIT License

     Copyright (c) 2018 Uwe Jantzen

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

    Klabautermann Software
    Uwe Jantzen
    Weingartener Straße 33
    76297 Stutensee
    Germany

    file        errors.h

    date        27.1.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Error code handling

    details     Defines the error codes and an error output function.

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#ifndef __H_ERRORS__
#define __H_ERRORS__


#define NOERR                                   0

#define ERR_ILLEGAL_STRING_LEGNTH               -1
#define ERR_NO_INIFILE                          -2
#define ERR_EOF                                 -3
#define ERR_UNKNOWN                             -4
#define ERR_ILLEGAL_KEYLINE                     -5
#define ERR_ILLEGAL_KEY_TYPE                    -6
#define ERR_OUT_OF_MEMORY                       -7
#define ERR_ILLEGAL_STRING_PTR                  -8
#define ERR_GET_FILE_LENGTH                     -9
#define ERR_NOT_ENOUGH_MEMORY                   -10
#define ERR_VAR_UNKNOWN                         -11
#define ERR_OPEN_FILE                           -12
#define ERR_PASSWORD_TO_LONG                    -13
#define ERR_OPEN_LOG_FILE                       -14
#define ERR_ILLEGAL_COMMANDLINE_ARGUMENT        -15
#define ERR_CURL_INIERROR                       -16
#define ERR_CURL_EASY_INIERROR                  -17
#define ERR_CURL_HEADERLISERROR                 -18
#define ERR_CURL_SETOPERROR                     -19
#define ERR_CURL_PERFORM_ERROR                  -20
#define ERR_RESET_COMMUNICATION                 -21
#define ERR_NO_FTP_SERVER                       -22
#define ERR_ILL_TIMER_SECOND                    -23


typedef int ERRNO;


extern void error( ERRNO err );


#endif  // __H_ERRORS__
