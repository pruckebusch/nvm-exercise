\mainpage Exercise non-volatile memory.
This repository contains the code for an example implementation of a general purpose non-volatile memory library.
The code can be found in \ref nvm-exercise.

\defgroup nvm-exercise NVM exercise.
\brief The exercise demonstrates how a general purpose NVM library can be build on embedded platforms. .
 
The nvm-exercise implementation consists of two parts:
   * tests/ unit test for gp-nvm-lib.
   * src/ source code for gp-nvm-lib.

## Compile and execute example
To run the example follow the steps listed below:
```bash
cd <REPO_DIR>/tests
make
./test-gp-nvm
```
To start from a clean NVM remove and create nvm.bin again:
```bash
cd <REPO_DIR>/tests
rm nvm.bin
touch nvm.bin
```
