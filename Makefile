#
#   Copyright (c) 2018 Uwe Jantzen
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.
#
#   Klabautermann Software
#   Uwe Jantzen
#   Weingartener Straße 33
#   76297 Stutensee
#   Germany
#
#   file        Makefile
#
#   date        26.12.2018
#
#   author      Uwe Jantzen (jantzen@klabautermann-software.de)
#
#   brief       Makefile for axisPush
#
#   details
#
#   project     axisPush
#   target      Linux
#   begin       26.12.2018
#
#   note
#
#   todo
#

vpath %.h include
vpath %.c src
vpath %.o obj

CC  := gcc
DSRC := src
DINC := include
DBIN := bin
DOBJ := obj
CONF := conf

OBJ := axisPush.o ftp.o http.o getargs.o data.o password.o errors.o debug.o

VERSION = 1.00

CFLAGS = -I $(DINC) -Wall -O3 -DVERSION=\"$(VERSION)\" -D_DEBUG_
CC_LDFLAGS = -lm

.c.o: $(DOBJ)
	$(CC) $(CFLAGS) -c $< -o $(DOBJ)/$@

####### Build rules

all: install axisPush

axisPush : $(OBJ) $(DBIN)
	$(CC) $(CFLAGS) -o $(DBIN)/$@ \
		$(DOBJ)/axisPush.o \
		$(DOBJ)/ftp.o \
		$(DOBJ)/http.o \
		$(DOBJ)/getargs.o \
		$(DOBJ)/data.o \
		$(DOBJ)/password.o \
		$(DOBJ)/errors.o \
		$(DOBJ)/debug.o \
		-lcurl \
		$(CC_LDFLAGS)

axisPush.o : axisPush.c data.h getargs.h ftp.h http.h debug.h

ftp.o : ftp.c ftp.h data.h debug.h

http.o : http.c http.h data.h debug.h

getargs.o : getargs.c data.h password.h getargs.h debug.h

data.o : data.c data.h password.h debug.h

password.o : password.c password.h debug.h

errors.o : errors.c errors.h data.h debug.h

debug.o : debug.c debug.h

####### create object and executable directory if missing
install:
	@if [ ! -d  $(DBIN) ]; then mkdir $(DBIN); fi
	@if [ ! -d  $(DOBJ) ]; then mkdir $(DOBJ); fi

####### cleanup all objects and executables
.PHONY clean:
clean:
	-rm -v -f $(DOBJ)/* $(DBIN)/*
	-rmdir $(DOBJ) $(DBIN)
