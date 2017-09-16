CXXFLAGS = -std=c++11 -Wall -Os -s
LDFLAGS =
LDLIBS =

PROG = sample1
OBJS = app_sdl.o app.o main.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $(OBJS) `sdl2-config --cflags --libs`

clean:
	rm -f $(PROG) $(OBJS)