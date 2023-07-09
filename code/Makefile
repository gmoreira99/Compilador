CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=comp
OBJS=comp.o lexico/Token.o lexico/TS.o lexico/Lex.o \
	 sintatico/Sintax.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	cp $(TARGET) /usr/local/bin

comp.o: lexico/Lex.h

lexico/Token.o: lexico/Tag.h

lexico/TS.o: lexico/Tag.h lexico/Token.h

lexico/Lex.o: lexico/Token.h lexico/TS.h

sintatico/Sintax.o: sintatico/Sintax.h lexico/Tag.h lexico/Lex.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<