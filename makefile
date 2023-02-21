CC = g++
CFLAGS = -g -wall
TARGET = randmst

all: $(TARGET)
 
	$(TARGET): $(TARGET).cc
				$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cc
 
  clean:
				$(RM) $(TARGET)

