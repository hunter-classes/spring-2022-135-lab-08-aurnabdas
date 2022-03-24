main: main.o imageio.o alter.o 
	g++ -o main main.o imageio.o alter.o

sample: sample.o imageio.o
	g++ -o sample sample.o imageio.o

sample.o: sample.cpp imageio.h

imageio.o: imageio.cpp imageio.h

main.o: main.cpp imageio.h alter.h

alter.o: alter.cpp alter.h imageio.h

clean:
	rm -f sample.o imageio.o main.o alter.o

remove: 
	rm -f taska-* taskb-* taskc-* taskd-* taske-* taskf-*