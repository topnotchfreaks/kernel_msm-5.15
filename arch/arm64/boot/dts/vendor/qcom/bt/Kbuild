ifeq ($(CONFIG_ARCH_KALAMA),y)
dtbo-y += kalama-bt.dtbo
endif

ifeq ($(CONFIG_ARCH_WAIPIO),y)
dtbo-y += waipio-bt.dtbo
dtbo-y += waipio-kiwi-bt.dtbo
endif

ifeq ($(CONFIG_ARCH_KHAJE),y)
dtbo-y += khaje-bt.dtbo
endif

ifeq ($(CONFIG_ARCH_KONA),y)
dtbo-y += kona-bt.dtbo
endif

ifeq ($(CONFIG_ARCH_CROW),y)
dtbo-y += crow-bt.dtbo
endif

ifeq ($(CONFIG_ARCH_TRINKET), y)
dtbo-y += trinket-bt-v1.dtbo
endif

always-y        := $(dtb-y) $(dtbo-y)
subdir-y        := $(dts-dirs)
clean-files     := *.dtb *.dtbo
