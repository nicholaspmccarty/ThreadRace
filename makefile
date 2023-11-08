CXX=g++
RM=rm -f
CPPFLAGS=-std=c++17 -Werror -Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Wnull-dereference -Wold-style-cast -Wdouble-promotion -Wshadow

SRCS=big_race.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: intro

intro: $(OBJS)
	$(CXX) $(CPPFLAGS) -o intro $(OBJS)

# Build all C++ files
depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend

# Clean compiled C++ files
clean:
	$(RM) $(OBJS)

# Clean tool
distclean: clean
	$(RM) *~ .depend intro

include .depend