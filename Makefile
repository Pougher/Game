TARGET ?= main
SRC_DIRS := ./src

CXX = clang++

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

GLFW_INCLUDES := $(shell pkg-config --cflags glfw3)
GLFW_LIBS := $(shell pkg-config --libs glfw3)

GLEW_INCLUDES := $(shell pkg-config --cflags glew)
GLEW_LIBS := $(shell pkg-config --libs glew)

EXT_LIBS := -Iext/glm

INC_FLAGS := $(EXT_LIBS) $(GLFW_INCLUDES) $(GLEW_INCLUDES)
LDFLAGS = -lm $(GLEW_LIBS) $(GLFW_LIBS)

ifneq ($(OS),Windows_NT)
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		useless := $(info Building for Darwin (macos))
		LDFLAGS += -framework OpenGl -framework IOKit -framework Cocoa
	else ifeq ($(UNAME_S),Linux)
		useless := $(info Building for linux (tested on Arch))
		LDFLAGS += -lGL
	endif
else
	useless := $(info Building for Windows (untested as of now))
endif

CPPFLAGS := \
	$(INC_FLAGS) -MMD -MP -O3 -Wall -Wextra -Werror -pedantic -std=c++20 -march=native

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

.PHONY: clean, count, linux
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

count:
	tokei src/ --exclude "stb_image.h" --exclude "open_simplex_noise.hpp"

print-%  : ; @echo $* = $($*)

-include $(DEPS)
