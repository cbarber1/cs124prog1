CC = g++
CFLAGS = -g -Wall -O3
TARGET = randmst

$(TARGET): $(TARGET).cc
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cc
 
clean:
	$(RM) $(TARGET)

