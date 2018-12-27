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

    file        getargs.c

    date        26.12.2018

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Read commnd line optiomns and arguments

    details

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "password.h"
#include "getargs.h"


/*  function        ERRNO handle_arg( char * str )

    brief           handle command line arguments

    param[in]       char * str

    return          ERRNO
*/
ERRNO handle_arg( char * str )
    {
    ERRNO error = NOERR;
    int len = 0;

    if( *str == '-' )
        {
        len = strlen(str);                                                      // get string length for further error detection
        if( len > 1)
            {
            switch( *(str+1) )
                {
                case 'd' :
                    set_debug(1);                                               // switch on debug mode
                    break;
                case 'h' :
                    printf("\naxisPush V%s (c) Uwe Jantzen (Klabautermann-Software) %s", VERSION, __DATE__);
                    printf("\n\nUsage:");
                    printf("\n        axisPush [options] [<configuration file>]");
                    printf("\nOptions:");
                    printf("\n        -d            debug, show more data (eg. ftp ...)");
                    printf("\n        -h            show this help then stop without doing anything more");
                    printf("\n        -c            start the password encoder");
                    printf("\n\nIf no configuration file name is given the file \"conf/axisPush.conf\" is used.");
                    printf("\n\n");
                    exit(error);
                    break;
                case 'c' :
                    error = encode();
                    if( error != NOERR )
                        printf("password coding failed!\n");
                    exit(error);
                    break;
                default :
                    error = ERR_ILLEGAL_COMMANDLINE_ARGUMENT;
                    break;
                }
            }
        else
            error = ERR_ILLEGAL_COMMANDLINE_ARGUMENT;
        }
    else
        set_ini_file(str);

    return error;
    }
