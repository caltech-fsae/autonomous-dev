INC = -I inc/
CFLAGS=-c -g -Wall
LDFLAGS=-lprotobuf-c


out/maptest: obj/map.o obj/maptest.o
	mkdir -p $(@D)
	$(CC) $(INC) $^ -o $@ $(LDFLAGS)

src/object.pb-c.c:
	protoc-c --c_out=./ src/object.proto

obj/map.o: src/map.c
	mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $^ -o $@

obj/maptest.o: tests/maptest.c
	mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $^ -o $@

clean:
	rm out/* obj/*
