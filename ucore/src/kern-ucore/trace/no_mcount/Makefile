ifdef UCONFIG_FTRACE
TARGET_CFLAGS := $(filter-out -pg, $(TARGET_CFLAGS))
# http://www.gnu.org/software/make/manual/make.html#Text-Functions
endif

obj-y := 

obj-$(UCONFIG_FTRACE) += trace_functions_graph.o

