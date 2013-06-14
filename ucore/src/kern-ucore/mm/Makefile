TARGET_CFLAGS += -pg
#TODO_LTY: remove this

obj-y := pmm.o shmem.o swap.o vmm.o
obj-$(UCONFIG_HEAP_SLAB) += slab.o
obj-$(UCONFIG_HEAP_SLOB) += slob.o
