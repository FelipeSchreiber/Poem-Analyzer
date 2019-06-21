CPP=g++
CPPFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LD=g++
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

all: programa

.cpp.o:
	$(CPP) $(CPPFLAGS) -o $@ -c $<

programa: main.o perlWrapper.o
	$(LD) -o $@ $? $(LDFLAGS)

clean:
	rm -f $(all) *.o
