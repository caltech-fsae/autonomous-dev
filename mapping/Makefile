INC = -I inc/
CFLAGS=-c -g -Wall
LDFLAGS=-lprotobuf-c


out/maptest: obj/object.pb-c.o obj/map.o obj/maptest.o
	mkdir -p $(@D)
	$(CC) $(INC) $^ -o $@ $(LDFLAGS)

inc/object.pb-c.c: src/object.proto
	protoc-c --c_out=./ --proto_path=src/ src/object.proto
	mv object.pb-c.* inc/
obj/object.pb-c.o: inc/object.pb-c.c
	mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $^ -o $@

obj/map.o: src/map.c
	mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $^ -o $@

obj/maptest.o: tests/maptest.c
	mkdir -p $(@D)
	$(CC) $(INC) $(CFLAGS) $^ -o $@

clean:
	-rm -r ./out ./obj
	-rm inc/object.pb-c.*
