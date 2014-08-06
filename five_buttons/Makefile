# 
# makefile Version 1.0T 10/1/14 Tutorial Makefile;  Makefile for Beagle Bone Cross Compile on Windows
#

# Set PROJECT to main.c file
PROJECT=fiveb

# Set RIPDRAW to directory for and ripdraw core 
RIPDRAW = ../ripdraw_core

# Directory for C-Source
# Set vpath to where the c files are for application and ripdraw core
# ./source is directory for application code
# $(RIPDRAW) is directory for ripdraw core 
vpath %.c $(CURDIR)/source $(RIPDRAW) 

# Directory for includes
# Set variable for where include files are 
# ./include for application code include files
CINCLUDE = $(CURDIR)/include 

# Directory for object files
OBJDIR = $(CURDIR)/object

# Other dependencies
DEPS = \
 Makefile \
 $(RIPDRAW)/*.h 
# $(CURDIR)/include/*.h 	NOTE no .h files for fiveb, uncomment if you add .h file

# Compiler object files 
# add name of any application files, other than main file (PROJECT)
COBJ = \
 $(OBJDIR)/$(PROJECT).o \
 $(OBJDIR)/ripdraw.o \
 $(OBJDIR)/ripdraw-serial.o

# gcc binaries to use for compile and link
CC = "C:\gcc-linaro\bin\arm-linux-gnueabihf-gcc.exe"
LD = "C:\gcc-linaro\bin\arm-linux-gnueabihf-gcc.exe"

# rm is part of yagarto-tools
SHELL = cmd
REMOVE = rm -f

# Build Compiler options by concatenating into one string
CFLAGS = -marm
CFLAGS += -O0 
CFLAGS += -g 
CFLAGS += -I$(CINCLUDE)
CFLAGS += -I$(RIPDRAW)

# for a better output
MSG_EMPTYLINE = . 
MSG_COMPILING = ---COMPILE--- 
MSG_LINKING = ---LINK--- 
MSG_SUCCESS = ---SUCCESS--- 

# Our favourite
all: $(PROJECT)

# Linker call
$(PROJECT): $(COBJ)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_LINKING)
	$(LD) -o $@ $^ $(CFLAGS)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_SUCCESS) $(PROJECT)

# Compiler call
$(COBJ): $(OBJDIR)/%.o: %.c $(DEPS)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_COMPILING) $<
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(REMOVE) $(OBJDIR)/*.o
	$(REMOVE) $(PROJECT)

