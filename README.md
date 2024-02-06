# Image Blur MPI Parallelization

## Overview

This program demonstrates the parallelization of an image blur algorithm using MPI (Message Passing Interface). The blur operation is applied to an image, distributing the workload across multiple MPI ranks for efficient processing.

## Features

1. **MPI Parallelization:** Utilizes MPI to distribute image processing tasks among multiple ranks, improving overall performance.

2. **Image I/O:** Reads an image (JPEG format) and processes it in parallel, achieving a blur effect.

3. **Dynamic Load Balancing:** Divides the image into segments and assigns each segment to different MPI ranks, ensuring balanced workload distribution.

## Implementation Details

- The program reads an image named "image.jpg" and applies a blur effect using a convolution kernel.
- MPI is used for parallelization, distributing the image processing workload among ranks.
- Load balancing is achieved by dividing the image into segments based on the number of MPI ranks.

## Results

- The program prints the processing time taken for the blur operation.
- The processed image is saved as "processedImage.jpg."

### Plot of Runtime vs Number of MPI Ranks

![imagg](https://github.com/sullivanm22/Parallelize-Image-Processing/assets/59747399/99bdd563-f134-43ec-8f7c-c318704ed3fb)

### Image

![image](https://github.com/sullivanm22/Parallelize-Image-Processing/assets/59747399/601d7692-4075-45ee-b32f-80b68af4730a)

### Processed Image

![processedImage](https://github.com/sullivanm22/Parallelize-Image-Processing/assets/59747399/994e32a5-4615-407c-bc57-3f4c263b1e04)

## Dependencies / Libraries Used

- MPI (Message Passing Interface)
- C Library - <math.h>
- C Library - <stdio.h>
- C Library - <stdlib.h>
