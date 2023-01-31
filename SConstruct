# -*- Python -*-

src_dir = "src/"
include_dir = "include/"
bin_dir = "bin/"
build_dir = "build/"

env = Environment()
env.Tool("compilation_db")
env.CompilationDatabase()

obj_files = [
    "menu",
    "engine",
    "io_2d_mouse",
    "io_mouse",
    "io_2d_no_mouse",
    "ugame",
    "mazzycat",
    "igame",
    "texture",
    "game",
    "font",
    "audio",
    "geometry"
]

cflags = [
    "-O2",
    "-Wall",
    "-Werror",
    "-I/usr/include/SDL2",
    "-D_REENTRANT",
    "-I/usr/include/libpng16",
    "-I/usr/include/python3.10",
    "-Iinclude/mazengine",
    "-DHWY_SHARED_DEFINE",
    "-lyaml-cpp",
    "-lSDL2_mixer",
    "-lSDL2_image",
    "-lSDL2_ttf",
    "-lSDL2",
    "-fPIC",
]

_target = ""
_src = ""
for f in obj_files:
    _target = bin_dir + f + ".o"
    _src = src_dir + f + ".cc"
    env.SharedObject(target=_target, source=_src, CCFLAGS=cflags)


env.SharedLibrary(
    target=bin_dir + "mazengine.so", source=["bin/" + o + ".o" for o in obj_files]
)
