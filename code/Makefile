all:
	${CC} -c -I ../../mandoc/  extract_text.c
	${CC} extract_text.o -L ../../mandoc/ -L /lib/x86_64-linux-gnu/  -lmandoc -lz -o extract_text
	${CC} -o words_to_trigrams words_to_trigrams.c

clean:
	rm -f extract_text words_to_trigrams *.o
