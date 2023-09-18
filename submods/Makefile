# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -DBX_CONFIG_DEBUG=0

BGFX_HEADERS =  -Ibgfx/include -Ibx/include -Ibimg/include -IRmlUi/Include

#LINKER_FLAGS specifies the libraries we're linking against
# C:\Users\Ademola\Documents\GitHub\bgfx_starter_template\submods\bgfx\.build\linux64_gcc\bin\libbgfx-shared-libRelease.so
LINKER_FLAGS = bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so RmlUi/build/libRmlCore.so.6.0 -lSDL2 -lGL -lX11 -ldl -lpthread -lrt -lglfw -lfreetype
# /submods/bgfx/.build/linux64_gcc/bin/libbgfx-shared-libRelease.so
#This is the target that compiles our executable

# shadercRelease \
#     -f v_simple.sc \
#     -o v_simple.bin \
#     --platform linux \
#     --type vertex \
#     --verbose \
#     -i bgfx/src
#     shadercRelease \
#     -f f_simple.sc \
#     -o f_simple.bin \
#     --platform linux \
#     --type fragment \
#     --verbose \
#     -i bgfx/src

# ./shadercRelease -f v_simple.sc -o v_simple.bin --platform linux --type vertex --verbose -i bgfx/src
# 	./shadercRelease -f f_simple.sc -o f_simple.bin --platform linux --type fragment --verbose -i bgfx/src
all : app.cpp
	clear
	$(CC) app.cpp -o app $(BGFX_HEADERS) $(COMPILER_FLAGS) $(LINKER_FLAGS)
	