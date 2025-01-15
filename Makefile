# Define required environment variables
#------------------------------------------------------------------------------------------------
PLATFORM              ?= PLATFORM_DESKTOP

# Define project variables
PROJECT_NAME          ?= ultrasuperspacerocks
PROJECT_VERSION       ?= 1.0
PROJECT_BUILD_PATH    ?= .

# Automatically find all .cpp files in the src directory
PROJECT_SOURCE_FILES  = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)

# raylib library variables
RAYLIB_VERSION       ?= 5.0
RAYLIB_PATH          ?= vendor/raylib

RAYLIB_INCLUDE_PATH   ?= $(RAYLIB_PATH)/src
RAYLIB_LIB_PATH      ?= $(RAYLIB_PATH)/src

# Library type used for raylib: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= RELEASE

# Emscripten path configuration
EMSDK_PATH          ?= $(HOME)/emsdk
EMSCRIPTEN_PATH     ?= $(EMSDK_PATH)/upstream/emscripten
EMCC                 = $(EMSCRIPTEN_PATH)/emcc
EMXX                 = $(EMSCRIPTEN_PATH)/em++

# Determine PLATFORM_OS in case PLATFORM_DESKTOP selected
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS = WINDOWS
        CXX = g++
    else
        UNAMEOS = $(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS = LINUX
            CXX = g++
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS = OSX
            CXX = clang++
        endif
    endif
else
    ifeq ($(PLATFORM),PLATFORM_WEB)
        # Explicitly set CXX to the full path of em++
        CXX = $(EMXX)
    endif
endif

# Define compiler flags
CXXFLAGS = -std=c++17 -Wall -I$(RAYLIB_INCLUDE_PATH) -Iinclude

ifeq ($(BUILD_MODE),DEBUG)
    CXXFLAGS += -g -O0 -D_DEBUG
else
    CXXFLAGS += -s -O2
endif

# Define linker flags
LDFLAGS = -L$(RAYLIB_LIB_PATH)

# Define libraries to link
ifeq ($(PLATFORM),PLATFORM_WEB)
    # Web specific flags and libraries
    LDLIBS = $(RAYLIB_LIB_PATH)/libraylib.a
    LDFLAGS += -s USE_GLFW=3 \
              -s TOTAL_MEMORY=134217728 \
              -s INITIAL_MEMORY=134217728 \
              -s ASYNCIFY \
              -s FORCE_FILESYSTEM=1 \
              -s ASSERTIONS=2 \
              -s SAFE_HEAP=1 \
              -s DEMANGLE_SUPPORT=1 \
              -s WASM=1 \
              -s ALLOW_MEMORY_GROWTH=1 \
              -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
              -s STACK_SIZE=5MB \
              -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'UTF8ToString', 'stringToUTF8', 'getValue', 'setValue']" \
              -s "EXPORTED_FUNCTIONS=['_main', '_malloc', '_free', '_realloc', '_memset', '_memcpy']" \
              -s NO_EXIT_RUNTIME=1 \
              -s ASYNCIFY_STACK_SIZE=24576 \
              -s ALLOW_TABLE_GROWTH \
              --preload-file resources@/ \
              --shell-file shell.html \
              -s GL_DEBUG \
              -s GL_ENABLE_GET_PROC_ADDRESS \
              --use-preload-plugins
    EXT = .html
else
    ifeq ($(PLATFORM_OS),WINDOWS)
        LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
        EXT = .exe
    endif
    ifeq ($(PLATFORM_OS),LINUX)
        LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
        EXT = 
    endif
    ifeq ($(PLATFORM_OS),OSX)
        LDLIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
        EXT = .app
    endif
endif

# Define all object files
OBJS = $(patsubst %.cpp, %.o, $(PROJECT_SOURCE_FILES))

# Default target entry
all: $(PROJECT_NAME)

# Generate shell.html for Web target
shell.html:
	echo "<!doctype html>" > shell.html
	echo "<html lang='en-us'><head>" >> shell.html
	echo "<meta charset='utf-8'>" >> shell.html
	echo "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>" >> shell.html
	echo "<title>Ultra Super Space Rocks</title>" >> shell.html
	echo "<style>" >> shell.html
	echo "body { margin: 0; background-color: black; }" >> shell.html
	echo "canvas.emscripten { position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); }" >> shell.html
	echo ".emscripten { padding-right: 0; margin-left: auto; margin-right: auto; display: block; }" >> shell.html
	echo "div.emscripten { text-align: center; }" >> shell.html
	echo "div.emscripten_border { border: 1px solid black; }" >> shell.html
	echo ".spinner { height: 30px; width: 30px; margin: 0; margin-top: 20px; margin-left: 20px; display: inline-block; vertical-align: top; }" >> shell.html
	echo "</style>" >> shell.html
	echo "</head>" >> shell.html
	echo "<body>" >> shell.html
	echo "<div class='emscripten_border'>" >> shell.html
	echo "  <canvas class='emscripten' id='canvas' oncontextmenu='event.preventDefault()'></canvas>" >> shell.html
	echo "</div>" >> shell.html
	echo "<script type='text/javascript'>" >> shell.html
	echo "  var Module = {" >> shell.html
	echo "    preRun: []," >> shell.html
	echo "    postRun: []," >> shell.html
	echo "    print: (function() {" >> shell.html
	echo "      return function(text) {" >> shell.html
	echo "        if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');" >> shell.html
	echo "        console.log(text);" >> shell.html
	echo "      };" >> shell.html
	echo "    })()," >> shell.html
	echo "    printErr: function(text) {" >> shell.html
	echo "      if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');" >> shell.html
	echo "      console.error(text);" >> shell.html
	echo "    }," >> shell.html
	echo "    canvas: (function() {" >> shell.html
	echo "      var canvas = document.getElementById('canvas');" >> shell.html
	echo "      canvas.addEventListener('webglcontextlost', function(e) { alert('WebGL context lost. You will need to reload the page.'); e.preventDefault(); }, false);" >> shell.html
	echo "      return canvas;" >> shell.html
	echo "    })()," >> shell.html
	echo "    setStatus: function(text) {" >> shell.html
	echo "      if (text) console.log('[Status]', text);" >> shell.html
	echo "    }" >> shell.html
	echo "  };" >> shell.html
	echo "</script>" >> shell.html
	echo "{{{ SCRIPT }}}" >> shell.html
	echo "</body></html>" >> shell.html

# Web Target - Compile raylib first, then the game
web: shell.html
	cd $(RAYLIB_PATH)/src && $(MAKE) clean && $(MAKE) -e PLATFORM=PLATFORM_WEB -B CC="$(EMCC)" AR="$(HOME)/emsdk/upstream/emscripten/emar" RAYLIB_BUILD_MODE=RELEASE
	$(MAKE) -e PLATFORM=PLATFORM_WEB $(PROJECT_NAME)

# Project target
$(PROJECT_NAME): $(OBJS)
	$(CXX) -o $(PROJECT_BUILD_PATH)/$(PROJECT_NAME)$(EXT) $(OBJS) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

# Compile source files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean everything
clean:
	rm -f $(OBJS)
	rm -f $(PROJECT_BUILD_PATH)/$(PROJECT_NAME)$(EXT)
	rm -f $(PROJECT_NAME).data $(PROJECT_NAME).html $(PROJECT_NAME).js $(PROJECT_NAME).wasm
	rm -f shell.html

.PHONY: all clean web