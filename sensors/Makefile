INC=-Iout/
CFLAGS=-c -g -Wall
LDFLAGS=-lprotobuf-c

all: sensorconfig sensors

protoTest: protoWrite protoRead
out/protoWrite.o: src/protoWrite.c
	gcc $(INC) $(CFLAGS) $^ -o $@
out/protoRead.o: src/protoRead.c
	gcc $(INC) $(CFLAGS) $^ -o $@
out/sensors.pb-c.o: out/sensors.pb-c.c
protoWrite: out/protoWrite.o out/sensors.pb-c.o
	gcc -o out/protoWrite $^ $(LDFLAGS)
protoRead: out/protoRead.o out/sensors.pb-c.o
	gcc -o out/protoRead $^ $(LDFLAGS)

sensors:
	gcc $(INC) -c out/sensors.pb-c.c -o out/sensors.pb-c.o
	gcc $(INC) -c out/ray.pb-c.c -o out/ray.pb-c.o
	gcc $(INC) -c src/camera_util.c -o out/camera_util.out

sensorconfig: out/sensors.pb-c.c

out/sensors.pb-c.c:
	mkdir -p out
	protoc-c --c_out=./out --proto_path=tools/ sensors.proto ray.proto

clean:
	rm out/*.o out/*.pb-c.* out/protoWrite
