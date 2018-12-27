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

    file        password.c

    date        27.12.2018

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       encode() encodes a value typed in by the user to a string to be
                saved in the ini file.
                decode() decodes the string from the ini file to a plain text
                value.

    details

    project     axisPush
    target      Linux
    begin       26.12.2018

    note        If your computer where this program is running on is accessible
                from outside your local network you should not save your ftp
                password using plain text.
                You can use these two functions to implement your own
                encoding/decoding algorithm.

    todo

*/


#include <ctype.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "password.h"


/*  function        ERRNO encode( void )

    brief           encodes the string typed in by the user to the value to be
                    stored in the .ini-file

    return          ERRNO
*/
ERRNO encode( void )
    {
    printf("Please enter the string to be encoded:\n");

    return NOERR;
    }


/*  function        ERRNO decode( char * * p_value, char * p_in )

    brief           decodes the encoded value
                    therefor allocates the memory

    param[out]      char * * p_value, pointer to the string to hold the decoded
                    string
    param[in]       char * p_in, pointer to string containing the encoded value

    return          ERRNO
*/
ERRNO decode( char * * p_value, char * p_in )
    {
    size_t len;

    if( !p_in )
        return ERR_ILLEGAL_STRING_PTR;
    len = strlen(p_in);

    *p_value = (char *)malloc(len + 1);
    if( !*p_value )
        return ERR_OUT_OF_MEMORY;

    strncpy(*p_value, p_in, len);
    (*p_value)[len] = 0;

    return NOERR;
    }
