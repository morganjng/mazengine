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

env.SharedLibrary(target="bin/maz_rb", source="src/maz_rb.cc",
                  CCFLAGS=cflags + ["-l" + dep for dep in library_deps]
                  + ["-I" + direc for direc in include_dirs])

_target = ""
_src = ""
for f in obj_files:
    _target = bin_dir + f + ".o"
    _src = src_dir + f + ".cc"
    env.SharedObject(target=_target, source=_src,
                     CCFLAGS=cflags + ["-l" + dep for dep in library_deps] +
                     ["-I" + direc for direc in include_dirs])


env.SharedLibrary(
    target=bin_dir + "mazengine.so", source=["bin/" + o + ".o" for o in obj_files]
)
