CXX = clang++ -std=c++23
CXXFLAGS = -Wall -Wextra -Werror 
LDLIBS += -lm
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: Out.txt Plot 

#solution proposed by AI

MAIN_OUTPUTS = Out.txt noisysignal.dat dftnoisysignal.dat fftnoisysignal.dat \
               filteredsignal.dat breitwigner.dat convolved.dat deconvolved.dat \
               wiener.dat wieneroptimal.dat lambda.dat

$(MAIN_OUTPUTS): main
	./main > Out.txt

main.o: linearalgebra.h ft.h
timing.o: linearalgebra.h ft.h
linearalgebra.o: linearalgebra.h
ft.o: ft.h
main: main.o linearalgebra.o ft.o
timing: timing.o linearalgebra.o ft.o

dft.times.data: timing
	rm -f $@
	for N in 64 128 256 512 1024 2048 4096 8192 16384; do \
		gtime --format "$$N %e" --output $@ --append \
		./$< -size $$N -algo dft 1>out 2>err ;\
	done

fft.times.data: timing
	rm -f $@
	for N in 64 128 256 512 1024 2048 4096 8192 16384; do \
		gtime --format "$$N %e" --output $@ --append \
		./$< -size $$N -algo fft 1>out 2>err ;\
	done


Plot: $(MAIN_OUTPUTS) dft.times.data fft.times.data
	gnuplot noisysignal.gp
	gnuplot dftnoisysignal.gp
	gnuplot idftnoisysignal.gp
	gnuplot filteredsignal.gp
	gnuplot ifftnoisysignal.gp
	gnuplot runtime.gp
	gnuplot breitwigner.gp
	gnuplot convolved.gp
	gnuplot deconvolved.gp
	gnuplot wiener.gp
	gnuplot lambda.gp

clean: 
	rm -f main timing *.o Out.txt *.dat out err *.svg *.pdf log.timing *.data fit.log

.PHONY: all clean Plot