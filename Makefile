CC = gcc

PROJ_NAME = Nyarutab

FLAGS = -no-pie -Wall -O3

RLDIR = ..\raylib

NDEBUG = -mwindows

LNK_LIBS = -L$(RLDIR)\src -lraylib -lm -lopengl32 -lgdi32 -lwinpthread -lwinmm -DPLATFORM_DESKTOP --static

INCLUDES = -I$(RLDIR)\src

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(OBJS)
	$(CC) $(FLAGS) -no-pie $(OBJS) $(NDEBUG) $(INCLUDES) $(LNK_LIBS) -o $(PROJ_NAME).exe
	../RCEDIT/RCEDIT.exe /I ./$(PROJ_NAME).exe ./icon.ico

-include $(DEPS)

run: all
	./$(PROJ_NAME).exe

%.o: %.c
	$(CC) $(FLAGS) $(DEFINES) $(NDEBUG) $(INCLUDES) -MMD -MP -o $@ -c $<
