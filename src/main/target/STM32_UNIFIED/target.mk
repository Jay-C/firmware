ifeq ($(TARGET), STM32F405)
F405_TARGETS += $(TARGET)

else
ifeq ($(TARGET), STM32F411)
F411_TARGETS += $(TARGET)

else
ifeq ($(TARGET), STM32F7X2)
F7X2RE_TARGETS += $(TARGET)

else
ifeq ($(TARGET), STM32F745)
F7X5XG_TARGETS += $(TARGET)

else # STM32H743
H743xI_TARGETS += $(TARGET)

endif
endif
endif
endif

ifeq ($(TARGET), $(filter $(TARGET), STM32F405 STM32F745 STM32H743))
# Use a full block (16 kB) of flash for custom defaults - with 1 MB flash we have more than we know how to use anyway

CUSTOM_DEFAULTS_EXTENDED = yes
endif

FEATURES       += VCP SDCARD_SPI SDCARD_SDIO ONBOARDFLASH

TARGET_SRC = \
    $(addprefix drivers/accgyro/,$(notdir $(wildcard $(SRC_DIR)/drivers/accgyro/*.c))) \
    $(ROOT)/lib/main/BoschSensortec/BMI270-Sensor-API/bmi270.c \
    $(addprefix drivers/barometer/,$(notdir $(wildcard $(SRC_DIR)/drivers/barometer/*.c))) \
    $(addprefix drivers/compass/,$(notdir $(wildcard $(SRC_DIR)/drivers/compass/*.c))) \
    drivers/max7456.c \
    drivers/vtx_rtc6705.c \
    drivers/vtx_rtc6705_soft_spi.c \
    rx/cc2500_common.c \
    rx/cc2500_frsky_shared.c \
    rx/cc2500_frsky_d.c \
    rx/cc2500_frsky_x.c \
    rx/cc2500_sfhss.c \
    rx/cc2500_redpine.c \
    rx/a7105_flysky.c \
    rx/cyrf6936_spektrum.c \
    drivers/rx/rx_cc2500.c \
    drivers/rx/rx_a7105.c \
    drivers/rx/rx_cyrf6936.c
