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

    file        http.c

    date        27.1.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Establish a http connection to the web server.
                Get an image from there.

    details

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>
#include "data.h"
#include "debug.h"
#include "http.h"


/*  function        static size_t _WriteCallback( void * contents, size_t size, size_t nmemb, void * userp )

    brief           Reads a part of data got via http to the memory given by userp

    param[in]       void * contents
    param[in]       size_t size
    param[in]       size_t nmemb
    param[out]      void * userp

    return          int, number of bytes copied
*/
static size_t _WriteCallback( void * contents, size_t size, size_t nmemb, void * userp )
    {
    Memory * mem = (Memory *)userp;
    size_t bytesToRead = size * nmemb;

    if( (mem->size + bytesToRead) > IMAGE_SIZE )                                 // just in case
        return 0;

    memcpy(&(mem->memory[mem->size]), contents, bytesToRead);
    mem->size += bytesToRead;

    return bytesToRead;
    }


/*  function        ERRNO PullFile( Memory * image )

    brief           Get an image from a web server using http protocol

    param[in]       Memory * image

    return          ERRNO, error code
*/
ERRNO PullFile( Memory * image )
    {
    CURL *curl_handle = 0;
    CURLcode res;
    char url[420];

    image->size = 0;    /* no data at this point */

    curl_handle = curl_easy_init();
    if( curl_handle )
        {
        sprintf(url, "http://%s/%s", http_server(), http_path());
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, _WriteCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, image);

        // Grab image
        res = curl_easy_perform(curl_handle);
        if( res )
            {
            error(ERR_CURL_PERFORM_ERROR);
            return ERR_CURL_PERFORM_ERROR;
            }
        }
        curl_easy_cleanup(curl_handle);

        return NOERR;
    }
