ifdef UCONFIG_FTRACE
TARGET_CFLAGS := $(filter-out -pg, $(TARGET_CFLAGS))
# http://www.gnu.org/software/make/manual/make.html#Text-Functions
endif

obj-$(UCONFIG_FTRACE) := ftrace.o

obj-$(UCONFIG_FTRACE) += test_ftrace_0.o test_ftrace_1.o
#TODO_LTY: change this

