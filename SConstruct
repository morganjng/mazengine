# -*- Python -*-

src_dir = "src/"
include_dir = "include/"
bin_dir = "bin/"
build_dir = "build/"

obj_files = [
    "dev",
    "menu",
    "tile_player",
    "engine",
    "tile_entity",
    "tile_renderer",
    "io_2d_mouse",
    "io_mouse",
    "io_2d_no_mouse",
    "tile_game",
    "u_game",
    "tile_map",
]

cflags = [
    "-Wall",
    "-Werror",
    "-I/usr/include/SDL2",
    "-D_REENTRANT",
    "-I/usr/include/libpng16",
    "-DHWY_SHARED_DEFINE",
    "-lyaml-cpp",
    "-lSDL2_mixer",
    "-lSDL2_image",
    "-lSDL2",
]

# StaticObject(target=build_dir + "test.o", source = test_file)

_target = ""
_src = ""
for f in obj_files:
    _target = bin_dir + f + ".o"
    _src = src_dir + f + ".cc"
    SharedObject(target=_target, source=_src, CCFLAGS=cflags)

# for f in test_files:
#     StaticObject(target=build_dir + f + ".o", source=src_dir + f + ".cc")

# Program(
#     "test.out",
#     [build_dir + f + ".o" for f in test_files]
#     + [bin_dir + f + ".o" for f in obj_files]
#     + [build_dir + "test.o"],
# )


SharedLibrary(
    target=bin_dir + "mazengine.so", source=["bin/" + o + ".o" for o in obj_files]
)
