#!/bin/sh
#
# configures pulseaudio (i.e. runs "meson build" on the sources so that we get
# the resulting version.h for the other header files.
#
# should be run from the repository top-level, i.e. as
# "hack/pulseaudio-configure.sh" and NOT directly as
# "./pulseaudio-configure.sh" to get the files to go to their correct places.
#
# only ever meant to run on linux, so see the Makefile target that calls this.
set -e
set -u

build_dir="./build"
mkdir -p "${build_dir}"

package_url="https://www.freedesktop.org/software/pulseaudio/releases/pulseaudio-17.0.tar.xz"
package_basename="$(basename "${package_url}")"
package_path="${build_dir}/${package_basename}"
checksum_url="${package_url}.sha256sum"
checksum_basename="$(basename "${checksum_url}")"
checksum_path="${build_dir}/${checksum_basename}"

# download the package if it does not exist or its checksum is invalid
if [ ! -f "${checksum_path}" ]; then
    curl --output-dir "${build_dir}" --progress-bar -LO "${checksum_url}";
fi

checksum_helper() {
    local checksum dir package
    dir="${1}"
    package="${2}"
    checksum="${3}"

    if ! (cd "${dir}" && sha256sum -c "${checksum}"); then
        echo "checksum mismatch, deleting package ${package}"
        echo rm -f "${checksum}"
        return 1
    fi

    return 0
}

if [ ! -f "${package_path}" ] || ! checksum_helper "${build_dir}" "${package_basename}" "${checksum_basename}"; then
    curl --output-dir "${build_dir}" --progress-bar -LO "${package_url}"

    # run this once more to check and delete an erroneous package
    if ! checksum_helper "${build_dir}" "${package_basename}" "${checksum_basename}"; then
        echo "package download failed, exiting"
        exit 1
    fi
fi

# ready to roll, just assume it's compressed tar like .tar.xz or .tar.gz
package_dir="${build_dir}/${package_basename%.*.*}"
rm -rf "${package_dir}"
tar xJf "${package_path}" -C "${build_dir}"

(cd "${package_dir}" && meson build)

# copy our precious headers
headers_dir="${build_dir}/pulse"
rm -rf "${headers_dir}"
mkdir "${headers_dir}"
cp -a "${package_dir}/src/pulse/"*.h "${headers_dir}"
cp -a "${package_dir}/build/src/pulse/version.h" "${headers_dir}"

echo "done"
