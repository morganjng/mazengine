"""Setup Python file for Mazengine Python bindings."""
from distutils.core import setup, Extension

maz_ext = Extension(
    name="maz",
    sources=["src/mazmodule.cc"],
    include_dirs=["/usr/include/SDL2",
                  "/usr/include/libpng16",
                  "include",
                  "/usr/include/python3.10"],
    libraries=["yaml-cpp", "SDL2", "SDL2_mixer", "SDL2_image", "SDL2_ttf"]
)

setup(
    name="maz",
    version="0.1.0",
    ext_modules=[maz_ext]
)
