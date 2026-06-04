# where to store the patches
patch_dir := ./patch
# pulseaudio sources location
pulse_dir := ./pulseaudio-17.0
# headers location
header_dir := $(pulse_dir)/src/pulse

# where we work with all the modifications
work_dir := ./pulse

# all header files except version.h
headers := $(shell find $(header_dir) -type f -name "*.h" -printf "%f\n")

default:
	@echo "available targets: build patch"

build:
	cd $(pulse_dir) && meson build
	mkdir -p $(work_dir)
	install -C -m 0664 $(pulse_dir)/build/src/pulse/version.h $(work_dir)

patch:
	mkdir -p $(patch_dir)
	for header in $(headers); do \
		diff -u $(header_dir)/$${header} $(work_dir)/$${header} > /dev/null; \
		if [ $${?} -eq 1 ]; then \
			diff -u $(header_dir)/$${header} $(work_dir)/$${header} > $(patch_dir)/$${header%.*}.patch; \
		fi; \
	done

.PHONY: build patch
