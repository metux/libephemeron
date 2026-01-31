
all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean

test: all
	(cd src && ./test)
