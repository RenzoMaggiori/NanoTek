# NanoTekSpice

## Overview

NanoTekSpice is a logic simulator designed for digital electronics. It enables users to build a graph representing digital electronic components and simulate their behavior based on a configuration file. The project is implemented in C++ and supports compilation via Makefile or CMake.

## Features

- **Chipsets:** NanoTekSpice supports various chipsets, including primitive ones like the 4081 and more complicated functions like microprocessors. Each chipset is composed of digital electronic components based on boolean logic.
- **Simulation:** Users can simulate the behavior of digital electronic components by injecting values into the graph and obtaining results.
- **Configuration File:** NanoTekSpice uses a configuration file to describe the graph structure, chipsets, and connections between components. The configuration file format includes sections for chipsets and links, allowing users to define and link components easily.
- **Error Handling:** The program provides comprehensive error handling, including lexical and syntactic error detection in the circuit file, handling of unknown component types or names, and prevention of duplicate component names.
- **Interactive Mode:** Users can interact with NanoTekSpice via command-line commands, including input value changes, simulation ticks, display of current values, and continuous simulation until interrupted.

## Installation

To compile NanoTekSpice, use the provided Makefile or CMake. Make sure to include all necessary source files, excluding unnecessary files like binaries, temporary files, or object files.

## Usage

After compiling NanoTekSpice, you can run it with a circuit file passed as a parameter. The program reads standard input for commands such as "exit," "display," "input=value," "simulate," and "loop." Ensure to follow the specified format for the configuration file and adhere to the provided sample executions for correct usage.

## Example
```
./nanotekspice ./test_files/nts_single/input_output.nts
> display
tick: 0
input(s):
  in: U
output(s):
  out: U
> in=1
> simulate
> display
tick: 1
input(s):
  in: 1
output(s):
  out: 1
> exit
```

## Technical Considerations

NanoTekSpice adheres to technical considerations, including the implementation of the `IComponent` interface, creation of new `IComponent` instances via factory methods, and proper handling of pointers and references to component classes.

## Authors

| [<img src="https://github.com/RenzoMaggiori.png?size=85" width=85><br><sub>Renzo Maggiori</sub>](https://github.com/RenzoMaggiori) | [<img src="https://github.com/G0nzal0zz.png?size=85" width=85><br><sub>Gonzalo Larroya</sub>](https://github.com/G0nzal0zz)
|:---:|:---:|
