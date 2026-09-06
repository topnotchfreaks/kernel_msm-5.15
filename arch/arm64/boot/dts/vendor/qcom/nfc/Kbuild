ifeq ($(CONFIG_ARCH_KALAMA),y)
dtbo-y += nxp/kalama-nfc.dtbo \
	  nxp/kalama-nfc-mtp.dtbo \
	  nxp/kalama-nfc-qrd.dtbo \
	  nxp/kalama-nfc-cdp.dtbo \
	  nxp/kalama-nfc-rcm.dtbo

dtbo-y += nxp/kalama-v2-nfc.dtbo \
	  nxp/kalama-v2-nfc-mtp.dtbo \
	  nxp/kalama-v2-nfc-qrd.dtbo \
	  nxp/kalama-v2-nfc-cdp.dtbo

dtbo-y += st/kalama-nfc.dtbo \
	  st/kalama-nfc-mtp.dtbo \
	  st/kalama-nfc-cdp.dtbo

dtbo-y += st/kalama-v2-nfc.dtbo \
	  st/kalama-v2-nfc-mtp.dtbo \
	  st/kalama-v2-nfc-cdp.dtbo
endif

ifeq ($(CONFIG_ARCH_KHAJE),y)
dtbo-y += nxp/khaje-nfc-idp.dtbo \
          nxp/khaje-nfc-qrd.dtbo \
          nxp/khaje-nfc-qrd-hvdcp3p5.dtbo \
          nxp/khaje-nfc-qrd-nowcd9375.dtbo
endif

ifeq ($(CONFIG_ARCH_CROWXYZ),y)
dtbo-y += st/crow-nfc.dtbo \
	  st/crow-nfc-atp.dtbo \
          st/crow-nfc-idp-wcd9395-wcd-dmic.dtbo \
	  st/crow-nfc-idp.dtbo
endif

ifeq ($(CONFIG_ARCH_CROW),y)
dtbo-y += nxp/crow-nfc.dtbo \
          nxp/crow-nfc-atp.dtbo \
          nxp/crow-nfc-idp.dtbo \
          nxp/crow-nfc-idp-wcd9395-wcd-dmic.dtbo \
          nxp/crow-nfc-qrd.dtbo \
          nxp/crow-nfc-rcm.dtbo
endif

ifeq ($(CONFIG_ARCH_TRINKET),y)
dtbo-y += nxp/trinket-nfc.dtbo \
	  nxp/trinket-nfc-mtp.dtbo \
	  nxp/trinket-nfc-qrd.dtbo \
	  nxp/trinket-nfc-cdp.dtbo \
	  nxp/trinket-nfc-rcm.dtbo
endif

always-y	:= $(dtb-y) $(dtbo-y)
subdir-y	:= $(dts-dirs)
clean-files	:= *.dtb *.dtbo
