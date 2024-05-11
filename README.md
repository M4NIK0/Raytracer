# Raytracer

## Blender 4.1

Epitech project to make a raytracer program in C++.\
The goal is to create a 3D scene with a camera and objects, and render it with raytracing methods.

## The team

[Louis CHABRERIE](mailto:louis.chabrerie@epitech.eu) ([GitHub](https://github.com/M4NIK0)) - Raytracing specialist\
[Léo DOBY](mailto:leo.doby@epitech.eu) ([GitHub](https://github.com/LeoDoby)) - Parsing master\
[Arthur BICHARA](mailto:arthur.bichara@epitech.eu) ([GitHub](https://github.com/ArthurBchr)) - Editor enthusiast\
[Ethan FLAK](mailto:ethan.flak@epitech.eu) ([GitHub](https://github.com/Eth22-Epitech)) - Objects magician

## How to use

### Dependencies

You need to install the following libraries to compile the project:
- SFML
- libconfig++

### Compilation

Using CMakelists.txt, you can compile the project with the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

### Execution

You can run the program with the following command:

```bash
./raytracer [scene_file] [output_file]
```

- `-h`\
Display help


- `-is [width] [height]`\
Set the image size, defaults to 800x600


- `-cs [width] [height]`\
Set the chunk size, defaults to 16x16


- `-t [n]`\
Set the number of threads, defaults to 1


- `-s [n]`\
Set the number of samples, defaults to 3


- `-b [n]`\
Set the number of bounces, defaults to 2


- `-dr [n]`\
Set the number of diffusion rays, defaults to 1


- `-rr [n]`\
Set the number of reflection rays, defaults to 1


- `-cli`\
Disable the graphical interface for headless execution


- `-ne`\
Disable preview editor


- `-ws [n]`\
Preview window size
