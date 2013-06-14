ifdef UCONFIG_FTRACE
TARGET_CFLAGS := $(filter-out -pg, $(TARGET_CFLAGS))
# http://www.gnu.org/software/make/manual/make.html#Text-Functions
endif

obj-y := 
#TODO_LTY: tsc.o

obj-$(UCONFIG_FTRACE) += ftrace.o

obj-$(UCONFIG_FTRACE) += test_ftrace.o 
#TODO_LTY: change this

