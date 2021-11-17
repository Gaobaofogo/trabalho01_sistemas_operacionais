cmake_minimum_required(VERSION 3.10)

# set the project name
project(Sequencial)

# add the executable
add_executable(
  prog
  main.c
  ../aux/matrix.c
)

# include_directories("../aux")
target_include_directories(prog PRIVATE "../aux")
# configure_file(../aux/matrix.h)

