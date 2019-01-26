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

    file        ftp.c

    date        27.12.2018

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       establish a ftp connection to the internet server
                push the weather data to a file on the server
                kill the connection

    details

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "ftp.h"
#include "debug.h"
#include "data.h"


/*  function        static size_t _read_callback( void * ptr, size_t size, size_t nmemb, void * stream )

    brief           copies a part of the string that is to be sent over the ftp connection
                    to the send buffer

    param[in]       void * ptr
    param[in]       size_t size
    param[in]       size_t nmemb,
    param[in]       void * stream,

    return          size_t, number of bytes transferred
*/
static size_t _read_callback( void * ptr, size_t size, size_t nmemb, void * stream )
    {
    Memory * mem = (Memory *)stream;
    size_t bytesToWrite = size * nmemb;

    if( bytesToWrite < 1 )
        return 0;

    if( mem->size )
        {
        if( bytesToWrite > mem->size )
            bytesToWrite = mem->size;
        memcpy(ptr, mem->memory, bytesToWrite);
        mem->memory += bytesToWrite;
        mem->size -= bytesToWrite;
        return bytesToWrite;
        }

    return 0;
    }


/*  function        ERRNO PushFile( Memory * image )

    brief           opens a ftp connection and transfers imnage to the
                    given file on the server

    return          ERRNO
*/
ERRNO PushFile( Memory * image )
    {
    ERRNO error = NOERR;
    CURL * curl = 0;
    char remote_url[420];
    char name_pass[272];
    char * p_memory = image->memory;

    if( strlen(ftp_server()) == 0 )
        return ERR_NO_FTP_SERVER;

    sprintf(remote_url, "ftp://%s/%s", ftp_server(), ftp_path());
    debug("%s\n", remote_url);

    sprintf(name_pass, "%s:%s", user_name(), user_key());
    debug("Set user name and key : %s\n", name_pass);

    curl = curl_easy_init();                                                    // get a curl handle
    if( !curl )
        {
        error = ERR_CURL_EASY_INIERROR;
        goto end_PushFile;
        }
    debug("Curl initialized\n");

    error = ERR_CURL_SETOPERROR;
    if( curl_easy_setopt(curl, CURLOPT_URL, remote_url) )                        // specify target
        goto setopt_PushFile;
    if( curl_easy_setopt(curl, CURLOPT_USERPWD, name_pass) )                    // set user and password
        goto setopt_PushFile;
    if( curl_easy_setopt(curl, CURLOPT_UPLOAD, 1) )                             // enable uploading
        goto setopt_PushFile;
    if( curl_easy_setopt(curl, CURLOPT_READFUNCTION, _read_callback) )          // we want to use our own read function
        goto setopt_PushFile;
    if( is_debug() )
        {
        if( curl_easy_setopt(curl, CURLOPT_VERBOSE, 1) )
            goto setopt_PushFile;
        }
    if( curl_easy_setopt(curl, CURLOPT_READDATA, image) )                       // now specify which file to upload
        goto setopt_PushFile;
    debug("Options set\n");

    /* Set the size of the file to upload (optional). If you give a *_LARGE
       option you MUST make sure that the type of the passed-in argument is a
       curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
       make sure that to pass in a type 'long' argument. */
    if( curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)image->size) )
        goto setopt_PushFile;
    debug("Filesize set set\n");

    error = NOERR;
    if( curl_easy_perform(curl) )                                               // Now run off and do what you've been told!
        error = ERR_CURL_PERFORM_ERROR;
    debug("Curl performed\n");
    image->memory = p_memory;                                                   // restore memory pointer

    free(image->memory);

setopt_PushFile:
    curl_easy_cleanup(curl);                                                    // always cleanup
    debug("Curl cleaned up\n");
end_PushFile:
    return error;
    }


/*  function        ERRNO FtpInit( void )

    brief           does the global init of the curl lib

    return          ERRNO
*/
ERRNO FtpInit( void )
    {
    debug("Initialize curl\n");
    return ( curl_global_init(CURL_GLOBAL_ALL) ) ? ERR_CURL_INIERROR : NOERR;
    }


/*  function        void FtpCleanup( void )

    brief           does the global cleanup of the curl lib
*/
void FtpCleanup( void )
    {
    curl_global_cleanup();
    }
