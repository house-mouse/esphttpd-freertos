#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := esphttpd

include $(IDF_PATH)/make/project.mk

HTMLDIR := html
ESPFSDIR := ../esp8266_rtos_toolchain/components/libesphttpd/espfs/
MKESPFSIMAGE := $(ESPFSDIR)/mkespfsimage/mkespfsimage
THISDIR := $(PWD)

webpages.espfs: $(HTMLDIR) $(MKESPFSIMAGE)
ifeq ("$(COMPRESS_W_YUI)","yes")
	$(Q) rm -rf html_compressed;
	$(Q) cp -r ../html html_compressed;
	$(Q) echo "Compression assets with yui-compressor. This may take a while..."
	$(Q) for file in `find html_compressed -type f -name "*.js"`; do $(YUI-COMPRESSOR) --type js $$file -o $$file; done
	$(Q) for file in `find html_compressed -type f -name "*.css"`; do $(YUI-COMPRESSOR) --type css $$file -o $$file; done
	$(Q) awk "BEGIN {printf \"YUI compression ratio was: %.2f%%\\n\", (`du -b -s html_compressed/ | sed 's/\([0-9]*\).*/\1/'`/`du -b -s ../html/ | sed 's/\([0-9]*\).*/\1/'`)*100}"
# mkespfsimage will compress html, css, svg and js files with gzip by default if enabled
# override with -g cmdline parameter
	$(Q) cd html_compressed; find . $(FIND_OPTIONS) | $(MKESPFSIMAGE) > $(THISDIR)/webpages.espfs; cd ..;
else
	$(Q) cd ../html; find . $(FIND_OPTIONS) | $(MKESPFSIMAGE) > $(THISDIR)/webpages.espfs; cd ..
endif

libwebpages-espfs.a: webpages.espfs
	$(Q) $(OBJCOPY) -I binary -O elf32-xtensa-le -B xtensa --rename-section .data=.irom0.literal \
                webpages.espfs build/webpages.espfs.o.tmp
	$(Q) $(LD) -nostdlib -Wl,-r build/webpages.espfs.o.tmp -o build/webpages.espfs.o -Wl,-T webpages.espfs.ld
	$(Q) $(AR) cru $@ build/webpages.espfs.o

espfs/mkespfsimage/mkespfsimage: espfs/mkespfsimage/
	$(Q) $(MAKE) -C espfs/mkespfsimage USE_HEATSHRINK="$(USE_HEATSHRINK)" GZIP_COMPRESSION="$(GZIP_COMPRESSION)"


