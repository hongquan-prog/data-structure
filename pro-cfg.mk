DIR_SRC := .
DIR_INC := . 

TYPE_INC := .h
TYPE_SRC := .cpp
TYPE_OBJ := .o 
TYPE_DEP := .dep 

DIR_PROJECT := $(realpath .)
DIR_BUILD := build
HOST_NAME := $(shell uname)

APP := $(DIR_BUILD)/target