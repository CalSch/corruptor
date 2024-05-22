# corruptor
This is a C program that randomly flips bits in a file. It works by reading in a file in 64 byte chunks (chunk size might change, and I'm planning on a dynamic chunk size in the future) and randomly deciding to mutate them. Mutating works by selecting a random byte to change, which bit to flip, then it flips the bit.

## Build
There's no dependencies (yet), just do `make create_dirs` to create `bin/` and `out/`, then run `make` to compile it.

## Usage
Currently the command line options are limited, and they don't follow any actual standard. The first argument is the file you want to corrupt, and the second argument determines the chance that a chunk will be corrupted (1=100% chance, 2=50% chance, 1000=0.1% chance, etc.)  
When you run the command (ex. `bin/corrupt image.jpg 1000`) it will corrupt it and output the new file to `out/filename` (in this case `out/image.jpg`).
