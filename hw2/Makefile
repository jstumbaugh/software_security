all: buffer_overflow

buffer_overflow: buffer_overflow.cpp
	@g++ -std=c++11 -fno-stack-protector buffer_overflow.cpp -o bo.exe
	@echo 0 > tmp.txt
	@echo "Compiled successfully"

run:
	@./bo.exe

clean:
	@rm -f bo.exe

reset:
	@echo 0 > tmp.txt
