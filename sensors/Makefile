INC=-Iout/

all: sensorconfig sensors

sensors:
	gcc $(INC) -c out/sensors.pb-c.c -o out/sensors.pb-c.o
	gcc $(INC) -c out/ray.pb-c.c -o out/ray.pb-c.o
	gcc $(INC) -c src/camera_util.c -o out/camera_util.out

sensorconfig: sensors.pb-c.c

sensors.pb-c.c:
	mkdir -p out
	protoc-c --c_out=./out --proto_path=tools/ sensors.proto ray.proto

clean:
	rm -r out
