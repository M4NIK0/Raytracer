# Raytracer

## Blender 4.1

Epitech project to make a raytracer program in C++.\
The goal was to create a 3D scene with a camera and objects, and then render it with raytracing algorithms.\

This repo is an archive of the whole project as it was presented in our 2nd year at Epitech.

## The team
| Name                                                                                         | Fields                |
|----------------------------------------------------------------------------------------------|-----------------------|
| [Louis CHABRERIE](mailto:louis.chabrerie@epitech.eu) ([GitHub](https://github.com/M4NIK0))   | Raytracing specialist |
| [Léo DOBY](mailto:leo.doby@epitech.eu) ([GitHub](https://github.com/LeoDoby))                | Parsing master        |
| [Arthur BICHARA](mailto:arthur.bichara@epitech.eu) ([GitHub](https://github.com/ArthurBchr)) | Editor enthusiast     |
| [Ethan FLAK](mailto:ethan.flak@epitech.eu) ([GitHub](https://github.com/Eth22-Epitech))      | Objects magician      |

## How to use

### Dependencies

You need to install the following libraries to compile the project:
- SFML
- libconfig++

### Build

Using CMakelists.txt, you can compile the project with the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

### Config example

```cfg
Camera = {
    fov = 120.0;
    position = [0.0, -4.0, 0.0];
    exposure = 10.0;
    sensitivity = 30.0;
    rotation = [90.0, 0.0, 0.0];
};

Objects = (
    {
        type = "sphere";
        radius = 1.0;
        position = [0.0, 0.0, 0.0];
        translationSpeed = [0.0, 0.0, 0.0];
        color = [255.0, 255.0, 255.0];
        emissionIntensity = 0.0;
        emissionColor = [0.0, 0.0, 0.0];
        reflexion = 0.0;
        glass = false;
        refracionIndex = 1.0;
    },
    {
        type = "sphere";
        radius = 0.5;
        position = [2.0, 2.0, -0.5];
        translationSpeed = [0.0, 0.0, 0.0];
        color = [255.0, 255.0, 255.0];
        emissionIntensity = 0.0;
        emissionColor = [0.0, 0.0, 0.0];
        reflexion = 1.0;
        glass = false;
        refracionIndex = 1.0;
    },
    {
        type = "sphere";
        radius = 0.25;
        position = [-0.5, -2.0, 0.5];
        translationSpeed = [0.0, 0.0, 0.0];
        color = [255.0, 255.0, 255.0];
        emissionIntensity = 0.0;
        emissionColor = [0.0, 0.0, 0.0];
        reflexion = 0.0;
        glass = true;
        refractionIndex = 1.4;
    },
    {
        type = "plane";
        normal = [0.0, 0.0, 1.0];
        position = [0.0, 0.0, -1.0];
        color = [255.0, 255.0, 255.0];
        emissionIntensity = 0.0;
        emissionColor = [0.0, 0.0, 0.0];
        reflexion = 0.0;
    },
);

Lights = (
    {
        type = "point";
        intensity = 800.0;
        position = {x=0.0; y=0.0; z=10.0};
        color = [255.0, 255.0, 255.0];
    },
    {
        type = "point";
        intensity = 5.0;
        position = {x=1.0; y=-2.0; z=-0.5};
        color = [255.0, 0.0, 0.0];
    },
    {
        type = "point";
        intensity = 5.0;
        position = {x=-1.0; y=-2.0; z=-0.5};
        color = [0.0, 255.0, 0.0];
    },
    {
        type = "point";
        intensity = 5.0;
        position = {x=0.0; y=-2.0; z=0.5};
        color = [0.0, 0.0, 255.0];
    },
);
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
