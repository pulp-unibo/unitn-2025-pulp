# APPLICATION NAME
APP = convolution

# SOURCE FILES
APP_SRCS = main.c pulp_nn_conv_u8_u8_i8.c pulp_nn_matmul_u8_i8_4x2.c pulp_nn_matmul_u8_i8_2x2.c

# NUMBER OF USED CLUSTER CORES
CORES ?= 1
OPTIMIZED_SIZE ?= 0

ifeq ($(OPTIMIZED_SIZE), 1)
APP_CFLAGS += -DOPTIMIZED_SIZE
endif	

# COMPILER FLAGS
APP_CFLAGS += -O3 -Iinclude -DNUM_CORES=$(CORES)
APP_LDFLAGS +=

include $(RULES_DIR)/pmsis_rules.mk
