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

    file        errors.c

    date        04.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Error code handling

    details     Defines description strings for the error codes.
                Implements a verbose error output function.

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#include <stdio.h>
#include "errors.h"
#include "data.h"


static char * errors[] =
    {
    "No error",                                                                 //   0
    "illegal string length",
    "no configuration file",
    "unexpected end of file",
    "unknown error",
    "configuration file : illegal key line",
    "configuration file : illegal key",
    "out of memory",
    "No string given",
    "",
    "",
    "",
    "Could not open file",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "Could not perfor CURL call",
    "",
    "",
    "Timer second not in [0..59]",
    0
    };


/*  function        void error( ERRNO err )

    brief           Prints a brief description of error "err" to stdout.

    param[in]       ERRNO err, code of error to describe.

*/
void error( ERRNO err )
    {
    int idx;
    int count;

    if( err == 0 )                                                              // no error - no output
        return;

    idx = (int)err * -1;                                                        // switch error code to index into the text array
    if( idx < 0 )                                                               // just in case
        {
        fprintf(stderr, "Error %3d --- This is an implementation bug! Error code should NOT be positive!\n", err);
        return;
        }

    for( count = 0; errors[count]; ++count )
        {
        if( idx == count )
            break;
        }

    if( errors[count] )
        fprintf(stderr, "Error %3d : %s\n", err, errors[count]);
    else
        fprintf(stderr, "Error %3d : unknown error code !\n", err);
    }
