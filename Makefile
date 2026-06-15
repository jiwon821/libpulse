# where to store the patches
patches_dir := ./patches
# where we work with all the modifications
work_dir := ./work
# for pulseaudio sources
build_dir := ./build
# original pulseaudio headers directory, as copied there by the configure target
# see hack/pulseaudio-configure.sh
headers_dir := $(build_dir)/pulse
# where to store patched result
pulse_dir := ./pulse


help:
	@echo "available targets:"
	@echo "  configure: configures pulseaudio headers under build/pulse/"
	@echo "  patches: creates patches under patches/ from work/ directory modifications"
	@echo "  pulse: creates the pulse/ directory by applying patches"

configure:
	hack/pulseaudio-configure.sh

patches:
# I guess we can safely remove this, as it's all in git anyway
	rm -rf $(patches_dir)
	mkdir $(patches_dir)

# diff all original headers with work dir headers
	for header in $(headers_dir)/*.h; do \
		name="$$(basename "$${header}")"; \
		diff -u "$${header}" "$(work_dir)/$${name}" > /dev/null; \
		if [ $${?} -eq 1 ]; then \
			diff -u "$${header}" "$(work_dir)/$${name}" > "$(patches_dir)/$${name%.*}.patch"; \
		fi; \
	done

pulse:
# this directory we can always get rid of
	rm -rf $(pulse_dir)
	cp -a $(headers_dir) $(pulse_dir)

# apply all patches
	for patch in $(patches_dir)/*.patch; do \
		name="$$(basename "$${patch}")"; \
		target="$(pulse_dir)/$${name%.*}.h"; \
		patch "$${target}" "$${patch}"; \
	done

.PHONY: configure patches pulse
