# STM32-LSM6DSL

## C driver to interface LSM6DSL 6-DOF IMU with an STM32 microcontroller

This driver is largely inspired by the work from ST. Instead of using files spread apart the BSP, this driver has the advantage of being self sufficient to interface this sensor with an ST microcontroller.

The driver itself is made of the files lsm6dsl.c and lsm6dsl.h.

It requires the files errors.h, console.h and console.c, which are common files for all my drivers. They are used to set up the error type (in errors.h) returned by some of the functions of the driver and to display data with the microcontroller on a terminal (in console.h and console.c). These files can be found here https://github.com/astarus-pyxis/stm32-common.

The file main.c is an example of main that uses the driver.

## How to use this driver in a project

To use this driver in an STM32 CMake project, the sensor peripheral shall be configured with CubeMX or directly in the code. This is not done by the driver.

The C files  lsm6dsl.c and console.c shall be placed in the Core > Src folder of the project, and lsm6dsl.h, errors.h and console.h in the Core > Inc folder.

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
    "Core/Src/console.c"
    "Core/Src/lsm6dsl.c"
)
```

## Licence & Warranty

This driver is licensed under GNU V3.0. It comes with no warranty.
