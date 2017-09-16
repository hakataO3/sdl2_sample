CXXFLAGS = -std=c++11 -Wall -g -MMD -MP -I.
LDFLAGS =
LDLIBS = -lSDL2_image

PROG = sample3
SRCS = main.cpp app.cpp
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=%.d)

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS) `sdl2-config --libs`

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< `sdl2-config --cflags`

clean:
	rm -f $(PROG) $(OBJS) $(DEPS)

-include $(DEPS)