include ../rules.mk

TARGET=libini.so
OBJS=libini.o
CFLAGS=-g -Wall -I../include
LDFLAGS=-shared
LIBS=

build:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS)