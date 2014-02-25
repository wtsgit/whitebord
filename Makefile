.m:
	clang -g -fobjc-arc -framework Foundation $< -o $@

%.exe : %.cs
	mcs $<

CFLAGS=-g -Wall -ansi -pedantic

ifdef USESTD11
CXXFLAGS=-g -Wall -std=c++11 -pedantic
else
CXXFLAGS=-g -Wall -std=c++98 -pedantic
endif

ifdef USE32BIT
CXXFLAGS+=-m32
CFLAGS+=-m32
endif

ifeq ($(OS), Darwin)
ifdef USESTD11
CXXFLAGS+=-stdlib=libc++
endif
endif

ifeq ($(OS), FreeBSD)
CXX=g++48
LDFLAGS=-Wl,-rpath,/usr/local/lib/gcc48
endif

all: $(PROG)

clean:
	@rm -rf *.dSYM a.out *.o *.so *.s *.exe
	@file * \
	  | egrep -e 'Mach-O (64-bit executable|executable)' \
	  	  -e 'ELF 64-bit.*executable.*FreeBSD' \
	  	  -e 'ELF 64-bit.*executable.*GNU/Linux' \
	  | cut -d\: -f1 \
	  | while read f ; do rm -f "$$f" ; done
