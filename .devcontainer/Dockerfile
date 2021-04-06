# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.158.0/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# Development tools
RUN apt-get update \
  && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install --no-install-recommends \
     gcc-10 \
     g++-10 \
     cmake \
     ninja-build \
  && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 10 \
  && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10

# Emscripten
COPY --from=emscripten/emsdk:2.0.16 /emsdk /emsdk
RUN /emsdk/emsdk activate 2.0.16
ENV PATH="/emsdk:/emsdk/node/14.15.5_64bit/bin:/emsdk/upstream/emscripten:${PATH}"