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
    "geometry",
]

include_dirs = [
    "/usr/include/SDL2",
    "/usr/include/ruby-3.0.0",
    "/usr/include/ruby-3.0.0/x86_64-linux",
    "include/mazengine",
    "extern/rice/include"
]

library_deps = [
    "yaml-cpp",
    "ruby",
    "SDL2",
    "SDL2_mixer",
    "SDL2_image",
    "SDL2_ttf",
]

cflags = [
    "-O2",
    "-Wall",
    "-Werror",
    "-D_REENTRANT",
    "-DHWY_SHARED_DEFINE",
    "-fPIC",
]

env.SharedObject(target=bin_dir + "maz_rb", source=src_dir + "maz_rb.cc",
                 CCFLAGS=cflags + ["-l" + dep for dep in library_deps]
                 + ["-I" + direc for direc in include_dirs])

env.SharedLibrary(target="maz_rb", source=bin_dir + "maz_rb")

_target = ""
_src = ""
for f in obj_files:
    _target = bin_dir + f
    _src = src_dir + f + ".cc"
    env.SharedObject(target=_target, source=_src,
                     CCFLAGS=cflags + ["-l" + dep for dep in library_deps] +
                     ["-I" + direc for direc in include_dirs])

env.SharedLibrary(
    target="mazengine", source=["bin/" + o for o in obj_files]
)
