[![Build Status](https://dev.azure.com/sarek0318/symlink-tree/_apis/build/status/Sarek.symlink-tree?branchName=master)](https://dev.azure.com/sarek0318/symlink-tree/_build/latest?definitionId=1&branchName=master) [![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause)

Symlink-Tree
============

This project takes a directory tree and a destination path as an input. It will recreate the directory in the destination path by creating directories and putting symbolic links to the original files into the destination path.

It will also try to preserver ownership. In order to successfully do so, it is recommended to run the program with `sudo`.