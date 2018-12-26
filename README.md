# axisPush

This application loads an image from an AXIS 2110 ip camera using http protocol.
Then it pushes it to a web server using ftp protocol.

## Why Doing This?

Many years ago I got two AXIS 2110 ip cameras which where a little expensive
those days. They worked fine over a couple of years, pushing their images to
my web server via ftp.

This year I changed my internet provider so I got a new account, password and
server name. When updating these data to the camera no ftp transfer was started
any more. I tried two cameras with the same result. Even after resetting them to
factory default nothing worked better. Also using a script and the scheduler
does not result in a picture on the webserver.

But I have some [Raspberry Pis](http://www.raspberrypi.org/) working on weather
data logging what is a boring and very small job to do by a linux cumputer.

So I decided to write a little program dong the work the camera will not do.

## The Program

The program uses the curl library and some of the experiences I made with my
program [weather23k](https://github.com/KlabautermannSW/weather23k).
