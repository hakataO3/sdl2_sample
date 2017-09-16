CXXFLAGS = -std=c++11 -Wall -Os -s
LDFLAGS =
LDLIBS = -lSDL2_ttf

PROG = sample2
OBJS = app_sdl.o app_sdl_ttf.o app.o main.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $(OBJS) `sdl2-config --cflags --libs`

clean:
	rm -f $(PROG) $(OBJS)