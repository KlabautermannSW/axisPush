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

    file        axisPush.c

    date        27.1.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       this file holds the main program

                get the necessary data from ini file

                every minute
                    read data from ws2300
                    log data to log file
                    push data to ftp server

    details

    project     axisPush
    target      Linux
    begin       axisPush

    note

    todo

*/


#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "data.h"
#include "getargs.h"
#include "http.h"
#include "ftp.h"


/*  function        int WaitForNextMinute( void )

    brief           waits for the next minute to half over

    return          int, 0 if timed out
*/
int WaitForNextMinute( void )
    {
    time_t t;
    int s = get_second();

    for( ; ; )
        {
        sleep(5);
        t = time(0) % 60;
        if( ( t >= s ) && ( t < (s + 5) ) )
            return 0;
        }
    }


/*  function        int main( int argc, char *argv[] )

    brief           main function :
                        reads arguments,
                        prepares http and ftp connection
                        reads the image from the camera
                        pushed the image to the web server
                        prints messages to console if in debug mode

    param[in]       int argc, number of command line parameters
    param[in]       char *argv[], command line parameter list

    return          int, error code
*/
int main( int argc, char *argv[] )
    {
    int i;
    Memory * image;
    ERRNO result = NOERR;

    if( argc > 0 )
        {
        for( i = 1; i < argc; ++i )
            {
            result = handle_arg(argv[i]);
            if( result )
                printf("Error in command line argument : %s\n", argv[i]);
            }
        }

    result = Init();
    if( result )
        {
        printf("General initialization error : %d, programm exiting!\n", result);
        return result;
        }
    result = FtpInit();
    if( result )
        {
        printf("FTP initialization error : %d, programm exiting!\n", result);
        return result;
        }

    image = get_image_ptr();

    for( ; ; )
        {
        result = PullFile(image);
        error(result);

        result = PushFile(image);
        error(result);

        WaitForNextMinute();
        }

    FtpCleanup();

    DeInit();

    return result;
    }
