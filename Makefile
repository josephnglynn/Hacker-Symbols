all : build

build :
	clang main.c -o hackerSymbols


run :
	./hackerSymbols

binary :
	./hackerSymbols -b

binary_green :
	./hackerSymbols -b -green

install :
	cp hackerSymbols /usr/bin

uninstall :
	rm /usr/bin/hackerSymbols

clean :
	rm hackerSymbols
