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

    file        data.h

    date        27.01.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Read and store data from .ini-file
                Store global data
                Hold some global types

    details

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#ifndef __DATA_H__
#define __DATA_H__


#include <stdio.h>
#include "errors.h"


#define IMAGE_SIZE                  0x80000                                     // the hekp in the camera says: image size with lowest compression is ~250k,
                                                                                // so 512k should be enough room to hold an image in all cases

typedef struct
    {
    char * memory;
    size_t size;
    } Memory;


extern void set_debug( char set );
extern char is_debug( void );
extern ERRNO set_ini_file( char * ini_file_name );
extern char * ftp_server( void );
extern char * user_name( void );
extern char * user_key( void );
extern char * ftp_path( void );
extern char * http_server( void );
extern char * http_path( void );
extern int get_second( void );
extern Memory * get_image_ptr( void );
extern ERRNO Init( void );
extern void DeInit( void );


#endif  // __DATA_H__
