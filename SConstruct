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
    "texture"
]

cflags = [
    "-O2",
    "-Wall",
    "-Werror",
    "-I/usr/include/SDL2",
    "-D_REENTRANT",
    "-I/usr/include/libpng16",
    "-DHWY_SHARED_DEFINE",
    "-lyaml-cpp",
    "-lSDL2_mixer",
    "-lSDL2_image",
    "-lSDL2_ttf",
    "-lSDL2",
    "-fPIC",
]

# StaticObject(target=build_dir + "test.o", source = test_file)

_target = ""
_src = ""
for f in obj_files:
    _target = bin_dir + f + ".o"
    _src = src_dir + f + ".cc"
    env.SharedObject(target=_target, source=_src, CCFLAGS=cflags)

# for f in test_files:
#     StaticObject(target=build_dir + f + ".o", source=src_dir + f + ".cc")

# Program(
#     "test.out",
#     [build_dir + f + ".o" for f in test_files]
#     + [bin_dir + f + ".o" for f in obj_files]
#     + [build_dir + "test.o"],
# )


env.SharedLibrary(
    target=bin_dir + "mazengine.so", source=["bin/" + o + ".o" for o in obj_files]
)
