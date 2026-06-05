# where to store the patches
patches_dir := ./patches
# pulseaudio sources location
#pulse_dir := ./pulseaudio-17.0
# headers location
#header_dir := $(pulse_dir)/src/pulse

# where the build headers are copied to
headers_dir := ./pulse

# where we work with all the modifications
work_dir := ./work

build_dir := ./build
pulseaudio_package_url := https://www.freedesktop.org/software/pulseaudio/releases/pulseaudio-17.0.tar.xz
pulseaudio_checksum_url := https://www.freedesktop.org/software/pulseaudio/releases/pulseaudio-17.0.tar.xz.sha256sum

# all header files except version.h
headers := $(shell find $(build_dir)/$(basename $(basename $(notdir $(pulseaudio_package_url))))/src/pulse -type f -name "*.h" -printf "%f\n")

default:
	@echo "available targets: build patch"

build:
	mkdir -p $(build_dir)

# download checksum first
	if [ ! -f "$(build_dir)/$(notdir $(pulseaudio_checksum_url))" ]; then \
		curl --output-dir "$(build_dir)" --progress-bar -LO "$(pulseaudio_checksum_url)"; \
	fi

# (re-)download package if it doesn't exist or checksum doesn't match
	download="no" && \
	cd $(build_dir) && \
	if [ -f "$(notdir $(pulseaudio_package_url))" ]; then \
		if ! sha256sum -c "$(notdir $(pulseaudio_checksum_url))"; then \
			download="yes"; \
		fi; \
	else \
		download="yes"; \
	fi; \
	if [ "$${download}" = "yes" ]; then \
		curl --progress-bar -LO "$(pulseaudio_package_url)"; \
		sha256sum -c "$(notdir $(pulseaudio_checksum_url))"; \
	fi

# oh my god, TODO
	rm -rf $(build_dir)/$(basename $(basename $(notdir $(pulseaudio_package_url))))
	tar xJf $(build_dir)/$(notdir $(pulseaudio_package_url)) -C $(build_dir)
	(cd $(build_dir)/$(basename $(basename $(notdir $(pulseaudio_package_url)))) && meson build)

# copy headers
	mkdir -p $(headers_dir)
	for header in $(headers); do \
		install -p -m 0664 $(build_dir)/$(basename $(basename $(notdir $(pulseaudio_package_url))))/src/pulse/$${header} $(headers_dir); \
	done
	install -p -m 0664 $(build_dir)/$(basename $(basename $(notdir $(pulseaudio_package_url))))/build/src/pulse/version.h $(headers_dir)

patches:
	mkdir -p $(patches_dir)
	for header in $(headers); do \
		diff -u $(headers_dir)/$${header} $(work_dir)/$${header} > /dev/null; \
		if [ $${?} -eq 1 ]; then \
			diff -u $(headers_dir)/$${header} $(work_dir)/$${header} > $(patches_dir)/$${header%.*}.patch; \
		fi; \
	done

.PHONY: build patch
