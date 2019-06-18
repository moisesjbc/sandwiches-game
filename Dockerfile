FROM ubuntu:18.08
MAINTAINER Moisés J. <moisesjbc@gmail.com>

# Update Ubuntu 18.08.
RUN export DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get upgrade -y

# Set environment variables.
ENV SFML_VERSION 2.5.1
ENV TGUI_VERSION 0.8.5
ENV M2G_VERSION 0.3.0
ENV TEMP_DIR /var/tmp/third-party
ENV SCRIPTS_DIR /var/tmp/build_deps
ENV THIRD_PARTY_DIR /opt/third-party

# Copy build scripts to Docker.
COPY ./build_deps $SCRIPTS_DIR
WORKDIR $SCRIPTS_DIR
RUN chmod +x $SCRIPTS_DIR/*.sh

RUN exit 1

# Install dependencies from Ubuntu repositories.
RUN ./install_packages.sh

# Prepare a directory for dependencies.
RUN mkdir $THIRD_PARTY_DIR

# Install SFML from source.
RUN $SCRIPTS_DIR/install_sfml.sh $SFML_VERSION $THIRD_PARTY_DIR
RUN exit 1

# Install TGUI from source.
RUN $SCRIPTS_DIR/install_tgui.sh $TGUI_VERSION $THIRD_PARTY_DIR

# Install m2g from source.
RUN $SCRIPTS_DIR/install_m2g.sh $M2G_VERSION $THIRD_PARTY_DIR

# Strip generated libraries.
RUN for library in `ls $THIRD_PARTY_DIR/lib/li*.so.*`; do sudo strip "$library"; done

WORKDIR /var/tmp/sandwiches-game

ENTRYPOINT cp /usr/lib/x86_64-linux-gnu/libtinyxml2.so.0.0.0 third-party/ubuntu_18_04_x86_64/lib && \
    cp -R /var/tmp/build_deps/third-party/* third-party/ubuntu_18_04_x86_64/ && \
    rm -rf CMakeFiles/ CMakeCache.txt && \
    cmake . && \
    make -j 6


