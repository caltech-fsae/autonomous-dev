all: sensorconfig

sensorconfig: sensorConfig.c configProto.pb-c.c
	gcc -o sensorconfig sensorConfig.c configProto.pb-c.c -lprotobuf-c

configProto.pb-c.c: configProto.proto
	protoc-c --c_out=./ configProto.proto

clean:
	rm sensorconfig configProto.pb-c.*
