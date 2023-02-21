# Scamper

Scamper is set to be a metroidvania-style game about a rodent exploring a haunted estate, as well as a resource of potentially reusable code for similar games in the Rust language. As such, the majority of development so far has been in a somewhat reusable format, and will eventually be ported to its own game engine. 

## Design

The actual code used is lightweight and should be easy to understand from an outside perspective. There is a simple game loop and all textures are loaded at the start of execution. Input and game particulars are separated out into their own files and effort should be put in to keeping moving parts as distinct as possible.
