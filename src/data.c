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

    file        data.c

    date        23.03.2019

    author      Uwe Jantzen (jantzen@klabautermann-software.de)

    brief       Read and store data from .ini-file
                Store global data

    details

    project     axisPush
    target      Linux
    begin       26.12.2018

    note

    todo

*/


#include <string.h>
#include <malloc.h>
#include "data.h"
#include "password.h"


//    type codes for _GetEntry(.)
#define    EMPTY                        0
#define    SECTION                      1
#define    KEY_VAL                      2


static char const * the_default_init_file_name = "conf/axisPush.conf";

static char * the_init_file_name = 0;
static char the_debug_flag = 0;
static char * the_ftp_server = 0;
static char * the_user_name = 0;
static char * the_ftp_path = 0;
static char * the_key = 0;
static char * the_http_server = 0;
static char * the_http_path = 0;
static int the_second = 0;

static Memory the_image;
static char the_memory[IMAGE_SIZE];


/*  function        void set_debug( char set )

    brief           set the verbosity

    param[in]       char set, 0 : quiet, other : show debug output
*/
void set_debug( char set )
    {
    the_debug_flag = set;
    }


/*  function        char is_debug( void )

    brief           get the verbosity

    return          char, 0 : quiet, other : show debug output
*/
char is_debug( void )
    {
    return the_debug_flag;
    }


/*  function        void set_ini_file( char * ini_file_name )

    brief           set the initialization file name into a global variable

    param[in]       char * ini_file_name
*/
ERRNO set_ini_file( char * ini_file_name )
    {
    ERRNO err = NOERR;
    size_t len = 0;

    if( !ini_file_name )
        return err;
    if( *ini_file_name )
        {
        len = strlen(ini_file_name) + 1;
        the_init_file_name = (char*)malloc(len);
        if( the_init_file_name )
            memcpy(the_init_file_name, ini_file_name, len);
        else
            err = ERR_OUT_OF_MEMORY;
        }
    return err;
    }


/*  function        char * ftp_server( void )

    brief           returns a pointer to the ftp server name  string

    return          char *, pointer to the ftp server name  string
*/
char * ftp_server( void )
    {
    return the_ftp_server;
    }


/*  function        char * user_name( void )

    brief           returns a pointer to the user name string

    return          char *, pointer to the user name string
*/
char * user_name( void )
    {
    return the_user_name;
    }


/*  function        char * user_key( void )

    brief           returns a pointer to the users' key string

    return          char *, pointer to the users' key string
*/
char * user_key( void )
    {
    return the_key;
    }


/*  function        char * ftp_log_path( void )

    brief           returns a pointer to the path for the log files on the server

    return          char *, pointer to the servers log file path string
*/
char * ftp_path( void )
    {
    return the_ftp_path;
    }


/*  function        char * http_server( void )

    brief           returns a pointer to the http server name  string

    return          char *, pointer to the http server name  string
*/
char * http_server( void )
    {
    return the_http_server;
    }


/*  function        char * http_path( void )

    brief           returns a pointer to the name of the file on the web server

    return          char *, pointer to name of the file on the web server
*/
char * http_path( void )
    {
    return the_http_path;
    }


/*  function        int get_second( void )

    brief           returns the second in a minute when to start image transfer

    return          int, the second
*/
int get_second( void )
    {
    return the_second;
    }


/*  function        Memory * get_image_ptr( void )

    brief           returns a pointer to the Memory struct that's to be used to
                    hold the image.

    return          Memory *
*/
Memory * get_image_ptr( void )
    {
    return &the_image;
    }


/*  function        static ERRNO _Remove( char * str, char chr )

    brief           Remove all occurences of chr in p_str.
                    Only if no errors occured the contents of str is changed.

    param[in]       char * p_str, pointer to a string closed with a 0x00
    param[in]       char chr, character to remove from string

    return          ERRNO, error code
*/
static ERRNO _Remove( char * str, char chr )
    {
    char * buffer;
    char * p_buffer;
    char * p_str;
    size_t len;
    size_t i;

    if( !str )
        return ERR_ILLEGAL_STRING_PTR;

    len = strlen(str) + 1;
    if( len == 1 )
        return NOERR;

    buffer = (char *)malloc(len);
    if( !buffer )
        return ERR_OUT_OF_MEMORY;

    memset(buffer, 0, len);
    p_str = str;
    p_buffer = buffer;
    for( i=0; i<len; ++i )
        {
        if( *p_str != chr )
            {
            *p_buffer = *p_str;
            ++p_buffer;
            }
        ++p_str;
        }

    strcpy(str, buffer);

    free(buffer);

    return NOERR;
    }


/*  function        ERRNO _GetEntry( FILE * p_file, char * p_section, char * p_key, char * p_val )

    brief           Reads a line from an .ini file.
                    Returns the name of the section which contains the actual key,
                    the actual key name and the key's value.
                    Additionally the result value is set accordingly to a possible
                    error condition.
                    Only if NOERR the strings contains a legal vaule!

    param[in]       FILE * p_file, pointer to ini file
    param[out]      char * p_section, pointer to section name
    param[out]      char * p_key, pointer to key name
    param[out]      char * p_val, pointer to key value

    return          ERRNO, error code
*/
ERRNO _GetEntry( FILE * p_file, char * p_section, char * p_key, char * p_val )
    {
    char buffer[1024];
    int type;
    int len;

    type = EMPTY;
    if( !p_file )
        {
        if( the_debug_flag )
            printf("data.c _GetEntry : NO FILE\n");
        return ERR_NO_INIFILE;
        }

    do
        {
        if( !fgets(buffer, 1020, p_file) )                                      // read one line from file
            {
            if( feof(p_file) )
                {
                if( the_debug_flag )
                    printf("data.c _GetEntry : END OF FILE\n");
                return ERR_EOF;
                }
            else
                {
                if( the_debug_flag )
                    printf("data.c _GetEntry : UNKNOWN ERROR\n");
                return ERR_UNKNOWN;
                }
            }
        if( *buffer == '#' )                                                    // comment line
            {
            if( the_debug_flag )
                printf("data.c _GetEntry : COMMENT\n");
            return NOERR;
            }

        if( (*buffer == '\n') || (*buffer == '\r') )                            // empty line
            {
            if( the_debug_flag )
                printf("data.c _GetEntry : NEWLINE\n");
            return NOERR;
            }

        if( *buffer == '[' )                                                    // begin of section identifier
            {
            type = SECTION;
            strcpy(p_section, buffer);
            _Remove(p_section, 0x0d);
            _Remove(p_section, 0x0a);
            _Remove(p_section, ' ');
            _Remove(p_section, '[');
            _Remove(p_section, ']');
            if( the_debug_flag )
                printf("data.c _GetEntry : SECTION %s\n", p_section);
            }
        else
            {
            // from here on this must be a key
            type = KEY_VAL;
            strcpy(p_key, buffer);
            _Remove(p_key, ' ');
            len = (int)(strchr(p_key, '=') - p_key);
            if( len == 0 )                                                      // if equal the "=" is missing
                {
                type = EMPTY;
                if( the_debug_flag )
                    printf("data.c _GetEntry : ILLEGAL KEY LINE %s\n", p_key);
                return ERR_ILLEGAL_KEYLINE;
                }
            strcpy(p_val, p_key + len + 1);                                     // value starts behinde the "="
            *(p_key + len) = 0x00;                                              // get key (everything in front of "=")
            _Remove(p_val, 0x0d);
            _Remove(p_val, 0x0a);
            _Remove(p_val, '"');
            if( the_debug_flag )
                printf("data.c _GetEntry :   SECTION = %s, KEY %s = %s\n", p_section, p_key, p_val);
            }
        }
    while( type != KEY_VAL );

    return NOERR;
    }


/*  function        ERRNO Init( void )

    brief           initializes the global viarables from the data from the
                    .ini file

    return          ERRNO, initialization error or success
*/
ERRNO Init( void )
    {
    FILE * p_inifile;
    ERRNO error = NOERR;
    char section[80];
    char key[80];
    char val[3*MAX_PASSWORD_LENGTH];

    if( !the_init_file_name )
        the_init_file_name = (char *)the_default_init_file_name;

    p_inifile = fopen(the_init_file_name, "r");
    if( !p_inifile )                                                            // no ini file found
        return ERR_NO_INIFILE;

    while( _GetEntry(p_inifile, section, key, val ) == NOERR )
        {
/*
        always use strncpy() for the strings at here and put a terminating 0 at the end of the buiffer !
        NOT DONE YET !!!!!
*/
        if( (strcmp(section, "FTP") == 0) && (strcmp(key, "server") == 0) )
            error = decode(&the_ftp_server, val);
        else if( (strcmp(section, "FTP") == 0) && (strcmp(key, "user") == 0) )
            error = decode(&the_user_name, val);
        else if( (strcmp(section, "FTP") == 0) && (strcmp(key, "key") == 0) )
            error = decode(&the_key, val);
        else if( (strcmp(section, "FTP") == 0) && (strcmp(key, "path") == 0) )
            error = decode(&the_ftp_path, val);
        else if( (strcmp(section, "HTTP") == 0) && (strcmp(key, "server") == 0) )
            {
            the_http_server = (char *)malloc(strlen(val) + 1);
            if( !the_http_server )
                error = ERR_OUT_OF_MEMORY;
            strcpy(the_http_server, val);
            }
        else if( (strcmp(section, "HTTP") == 0) && (strcmp(key, "path") == 0) )
            {
            the_http_path = (char *)malloc(strlen(val) + 1);
            if( !the_http_path )
                error = ERR_OUT_OF_MEMORY;
            strcpy(the_http_path, val);
            }
        else if( (strcmp(section, "Timer") == 0) && (strcmp(key, "s") == 0) )
            {
            int s;

            sscanf(val, "%d", &s);
            if( ( s >= 0 ) && ( s < 54 ) )
                the_second = s;
            else
                error = ERR_ILL_TIMER_SECOND;
            }
        key[0] = 0;
        }

    fclose(p_inifile);

    the_image.memory = the_memory;
    memset(the_memory, 0, IMAGE_SIZE);

    return error;
    }


/*  function        void DeInit( void )

    brief           Free all allocated memory
*/
void DeInit( void )
    {
    free(the_ftp_server);
    free(the_user_name);
    free(the_ftp_path);
    free(the_key);
    free(the_http_server);
    free(the_http_path);
    }
