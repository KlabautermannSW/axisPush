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

    file        password.h

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


#ifndef __PASSWORD_H__
#define __PASSWORD_H__


#include "errors.h"


#define MAX_PASSWORD_LENGTH                     128


extern ERRNO encode( void );
extern ERRNO decode( char * * p_value, char * p_in );


#endif  // __PASSWORD_H__
