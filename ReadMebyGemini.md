# LC-3 Virtual Machine Implementation in C

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)
![License](https://img.shields.io/badge/license-MIT-green)

A low-level simulation of the **LC-3 (Little Computer 3)** architecture written in pure C. This project emulates the hardware components of the LC-3 computer, capable of executing assembly object files, including a fully playable version of the **2048 game**.

## 📖 Overview

This project was built to understand the fundamentals of **Computer Architecture**, specifically:
- How a CPU fetches, decodes, and executes instructions.
- How software interacts with hardware via **Memory Mapped I/O**.
- Managing registers, memory, and trap routines at a low level.

## ✨ Key Features

* **Full Instruction Set:** Implements all standard LC-3 opcodes (`ADD`, `AND`, `NOT`, `BR`, `JMP`, `JSR`, `LD`, `LDI`, `LDR`, `LEA`, `ST`, `STI`, `STR`, `TRAP`).
* **Trap Routines:** Handles system calls for I/O (`GETC`, `OUT`, `PUTS`, `IN`, `PUTSP`, `HALT`).
* **Condition Flags:** Accurate simulation of Positive (P), Zero (Z), and Negative (N) flags.
* **Windows Optimization (Custom):**
    * Implemented custom input buffering disablement for Windows Terminal.
    * **Smart Input Filtering:** Fixed the common `\r\n` issue on Windows by filtering out carriage returns, preventing "Invalid Input" errors in games.
    * Enabled **ANSI Escape Codes** support for rich UI rendering.

## 🚀 How to Build & Run

### Prerequisites
* GCC Compiler (MinGW for Windows or standard GCC for Unix-like systems).

### Compilation
Open your terminal in the project directory and run:

```bash
gcc lc3_vm.c -o lc3_vm