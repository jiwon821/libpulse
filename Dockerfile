FROM debian:trixie

RUN apt-get update \
 && apt-get install --assume-yes --no-install-recommends build-essential \
      ca-certificates check curl doxygen git libltdl-dev libsndfile1-dev \
      libtdb-dev make meson pkg-config xz-utils zip

COPY . /libpulse
WORKDIR /libpulse

RUN make configure && make pulse && zip pulse.zip pulse/*.h