ROOTFLAGS=`root-config --cflags --libs` 
CXXDEPFLAGS = -MMD -MP

all: main

main:  TrigEff.o \
       main.C 
	g++ --std=c++11 $^ -o Run.exe ${ROOTFLAGS} ${CXXDEPFLAGS}

%.o: %.C  
	g++ --std=c++11 -c $^ -o $@ ${ROOTFLAGS} ${CXXDEPFLAGS} 

clean:
	rm -f  *.{o,d,exe}
