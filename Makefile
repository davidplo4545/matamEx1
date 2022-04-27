CC = gcc
OBJS = RLEList.o tool/AsciiArtTool.o tool/main.o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
CFLAGS =-std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $(EXEC)

tool/main.o: tool/main.c tool/AsciiArtTool.h RLEList.h

tool/AsciiArtTool.o:tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h

RLEList.o: RLEList.c RLEList.h

clean:
	rm -f $(OBJS) $(EXEC)