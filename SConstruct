# -*- Python -*-

src_dir = "src/"
include_dir = "include/"
bin_dir = "bin/"
test_dir = "test/"

obj_files = [
    "dev",
    "menu",
    "tile_player",
    "engine",
    "tile_entity",
    "tile_renderer",
    "io_2d_mouse",
    "io_2d_no_mouse",
    "tile_game",
    "u_game",
    "tile_map",
]


_target = ""
_src = ""
for f in obj_files:
    _target = bin_dir + f + ".o"
    _src = src_dir + f + ".cc"
    StaticObject(
        target=_target,
        source=_src,
        CCFLAGS=["-Wall", "-Werror", "-lSDL2_image", "-I/usr/include/SDL2"],
    )
