CC=gcc
DB=db.txt

all: hs c java py

hs: r222.hs
	ghc -O3 $< -o $@

c: r222.c
	$(CC) -O3 $< -o $@

java: r222.java
	javac $<
	echo "#/bin/bash" >$@
	echo "java r222" >>$@
	chmod u+x $@

py: r222.py
	echo "#/bin/bash" >$@
	echo "python3 r222.py" >>$@
	chmod u+x $@

bench: hs c java py
	./bench.sh $^

clean:
	@rm -f c hs py java *.class *.o *.hi $(DB)
	@echo "removed intermediate build results and db [$(DB)]"

