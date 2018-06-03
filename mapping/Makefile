INC = -I inc/
CFLAGS=-c -g -Wall
LDFLAGS=-lprotobuf-c


out/maptest: obj/voxel.pb-c.o obj/map.o obj/maptest.o
	mkdir -p $(@D)
	$(CC) $(INC) $^ -o $@ $(LDFLAGS)

inc/voxel.pb-c.c: src/voxel.proto
	protoc-c --c_out=./ --proto_path=src/ src/voxel.proto
	mv voxel.pb-c.* inc/
obj/voxel.pb-c.o: inc/voxel.pb-c.c
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
	-rm inc/voxel.pb-c.*
