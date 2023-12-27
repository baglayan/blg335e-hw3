# 2023-2024 Fall Analysis of Algorithms 1 Project 3

[![C++ Lint with cppcheck](https://github.com/baglayan/blg335e-hw3/actions/workflows/cpp-lint.yml/badge.svg)](https://github.com/baglayan/blg335e-hw3/actions/workflows/cpp-lint.yml)
[![Docker build, run, test](https://github.com/baglayan/blg335e-hw3/actions/workflows/docker-image.yml/badge.svg)](https://github.com/baglayan/blg335e-hw3/actions/workflows/docker-image.yml)

## Introduction

This project implements algorithms for binary search tree and red black tree data structures.

## How to Build and Run

To build and run this project:
1. Clone the repository.
2. Navigate to the project directory.
3. Execute `g++ main.cpp -o main`
4. Run the execute with the following format: `../main <DATASET_FILE_NAME>.csv out.csv [v]`

## GitHub Workflows

### Docker Build and Run

This workflow builds a Docker image and compiles the QuickSort code whenever changes are pushed to the `main` branch or a pull request is made. It runs QuickSort for all populations and all pivoting strategies with threshold 1, and for all population with randomized pivot strategy for several different thresholds.

### C++ Linting

This workflow performs linting on the QuickSort.cpp file using cppcheck.

## Notice

This repository was made public after the submission date.