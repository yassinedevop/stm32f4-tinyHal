# Tiny HAL for STM32F407xx

This is a tiny template for an STM32F407 project, which includes a simple hello world message through USART2.

The HAL library is implemented from scratch, for the minimal functionality required for the project, obviously, the HAL library is not complete.

I always find make files to be a bit confusing, so I decided to use [Ceedling](http://www.throwtheswitch.org/ceedling) to build the project.

## Current implemented drivers
- UART Drivers
- GPIO Drivers
- RCC Drivers
- Flash Drivers
- CRC Drivers

## Getting Started 🚀
To get started with this project, follow these steps:

1. Clone the repository.
2. Install the necessary dependencies.
3. Build the project.
4. Flash the firmware onto your STM32F407 board.

## Dependencies 📦

No external dependencies are required to build this project.

## Building the Project 🛠️

Install ceedling, it is a build system for C projects that is used to build the project.

    gem install ceedling

Then run the following command to build the project.

    ceedling release

A generated .elf will be created in the build/release/ folder.

to clean the project run the following command.

    ceedling clean

## Flashing the Firmware 🔌

I don't have the board, if you are either you can test the project using a simulator i.e [renode](https://www.renode.io).

    renode helo.resc

Then start the simulation with the following command.

    start

A hello world message will be displayed in the console.

## Contributing 🤝
Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## Give a Star! ⭐
If you found this project helpful, please give it a star. It's a quick way to show that you care and it helps me understand which projects people find the most interesting.

## License 📝
This project is licensed under the [MIT License](LICENSE).