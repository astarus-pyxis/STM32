# STM32-RGB-LED

## C driver to interface a DS2406 with an STM32 microcontroller

The driver itself is made of the files ds2406.c and ds2406.h.

It requires the file errors.h, which is a common file for all my drivers. It is used to set up the error type returned by some of the functions of the driver. This file can be found here https://github.com/astarus-pyxis/stm32-common.

## How to use this driver in a project

To use this driver in an STM32 CMake project, the file  ds2406.c shall be placed in the Core > Src folder of the project, and ds2406.h and errors.h in the Core > Inc folder.

It also requires to add the sources to executable in the CMakeLists.txt file at the root of the project. To do this, the following at line 48 of this file.


```
# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

```

shall be changed to


```
# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    "Core/Src/ds2406.c"
)
```

## Licence & Warranty

This driver is licensed under GNU V3.0. It comes with no warranty.
