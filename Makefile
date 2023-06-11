build:
	g++ -std=c++20  main.cpp genCode/genCode.cpp parser/parser.cpp symbolTable/symbolTable.cpp utils/utils.cpp  -o main
run:
	./main
execute:
	rm -rf output/*.hack && make build && make run