# axisPush

This application loads an image from an AXIS 2110 ip camera using http protocol.
Then it pushes it to a web server using ftp protocol.

## Why Doing This?

Many years ago I got two AXIS 2110 ip cameras which where expensive
those days. They worked fine over a couple of years, pushing their images to
my web server via ftp.

This year I changed my internet provider so I got a new account, password and
server name. When updating these data to a camera no ftp transfer was started
any more. I tried two cameras with the same result. Even after resetting them to
factory default nothing worked better. Also using a script and the scheduler
does not result in a picture on the web server.

But I have some [Raspberry Pis](http://www.raspberrypi.org/) working on weather
data logging what is a boring and very small job to do for a linux cumputer.

So I decided to write a little program doing the work the cameras will not do.

## The Program

The program uses the curl library and some of the experiences I made with my
program [weather23k](https://github.com/KlabautermannSW/weather23k).

### How to use it:

```
$ bin/axisPush -h

axisPush V1.00 (c) Uwe Jantzen (Klabautermann-Software) Dec 27 2018

Usage:
        axisPush [options] [<configuration file>]
Options:
        -d            debug, show more data (eg. ftp ...)
        -h            show this help then stop without doing anything more
        -c            start the password encoder

If no configuration file name is given the file "conf/axisPush.conf" is used.
```

### Using the program as a systemd service

First you need a service file at /usr/lib/systemd/system named axisPush.service. A sample can be found in the dirctory systemd.

Then set the security flags as follows:
```
chmod 644 /usr/lib/systemd/system/axisPush.service
```
At last you have to enable and start the service:
```
systemctl enable axisPush.service
systemctl start axisPush.service
```
That's it!

## Remarks

You have to install libcurl on every computer you want the program to run on and
libcurl-dev or something similiar on the computer where you compile the program.

There is no encoder/decoder given. You may add your own preferred algorithm to
the functions.
