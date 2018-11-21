# Points to the root of Lib MARIO
MARIO_DIR = .

# Flags passed to the preprocessor
CPPFLAGS +=

#Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -DLINUX32 
CFLAGS += -g -Wall -DLINUX32 -fPIC -D__DEBUG__ -std=c99


MARIO_HEADER = $(MARIO_DIR)/*.h
MARIO_SRCS = $(MARIO_DIR)/*.c $(MARIO_HEADER)

all : libmario.a

.PHONY : clean
clean:
	-rm -f libmario.a *.o

mario.o : $(MARIO_SRCS) 
	$(CXX) $(CXXFLAGS) -I$(MARIO_DIR) -c $(MARIO_DIR)/mario.c


# gcc $(CFLAGS) -I$(MARIO_DIR) -c $(MARIO_DIR)/mario.c

libmario.a : mario.o
	$(AR) $(ARFLAGS) $@ $^

