# https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
# a lot of good info here: 
#       https://www.gnu.org/software/make/manual/
#       https://github.com/amjadmajid/Makefile
# use := instead of = to immediately expand variables: https://www.gnu.org/software/make/manual/html_node/Flavors.html#Flavors
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -pthread

TARGET = beamng-autodrive
OBJS = \
	src/main.o \
	src/beamngStream.o \

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
