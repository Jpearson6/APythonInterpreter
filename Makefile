.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++20
objects =  Token.o NumberDescriptor.o Tokenizer.o Parser.o Expr.o SymTab.o Statements.o main.o

statement.x: $(objects)
	g++ $(CFLAGS) -o statement.x $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@


Token.o:  Token.cpp Token.hpp
NumberDescriptor.o: NumberDescriptor.cpp NumberDescriptor.hpp
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp
Expr.o: Expr.cpp Expr.hpp Token.hpp SymTab.hpp NumberDescriptor.hpp
SymTab.o: SymTab.cpp SymTab.hpp NumberDescriptor.hpp
Parser.o: Parser.cpp Token.hpp Parser.hpp Tokenizer.hpp SymTab.hpp Expr.hpp Statements.hpp NumberDescriptor.hpp
Statements.o: Statements.cpp Statements.hpp Expr.hpp Token.hpp SymTab.hpp NumberDescriptor.hpp
main.o: main.cpp Token.hpp Tokenizer.hpp Parser.hpp SymTab.hpp Expr.hpp Statements.hpp NumberDescriptor.hpp

clean:
	rm -fr *.o *~ *.x
