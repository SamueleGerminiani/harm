# HARM with its optional tools (H11, D-027): Z3 (--reduce equiv/implies, --atom-premises), harm-coi
# (RTL cones and predicates, Python + pyslang), Verilator, Icarus and yosys (the simulation oracles and
# the cross-check; built from source by third_party/install_all.sh, H11d).
# HARM_REF selects what is built: "dev" until the release (the merge into main and the tag v4 are
# deferred), then a tag.
FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
        git build-essential uuid-dev pkg-config wget unzip \
        python3 python3-dev python3-venv \
        autoconf flex bison help2man gperf perl gawk libfl-dev zlib1g-dev libreadline-dev \
        tcl-dev libffi-dev \
    && rm -rf /var/lib/apt/lists/*
ENV PYTHON=python3

RUN wget -q https://github.com/Kitware/CMake/releases/download/v3.31.1/cmake-3.31.1-linux-x86_64.sh -O cmake.sh \
    && chmod +x cmake.sh \
    && ./cmake.sh --prefix=/usr/local --exclude-subdir --skip-license \
    && rm cmake.sh

ARG HARM_REPO=https://github.com/SamueleGerminiani/harm.git
ARG HARM_REF=dev
# no cache from here, so that the ref is fetched again
ARG CACHE_DATE=not_a_date
RUN git clone ${HARM_REPO} /harm && cd /harm && git checkout ${HARM_REF}

# third-party libraries (antlr4, Spot, Boost, Z3), built with the same compiler as HARM (D-010),
# and the tools (Verilator, Icarus, yosys with read_slang), H11d
WORKDIR /harm/third_party
RUN bash ./install_all.sh

# harm-coi in its own virtual environment (Python >= 3.11; Ubuntu 24.04 has 3.12)
RUN python3 -m venv /opt/harm-coi && /opt/harm-coi/bin/pip install --no-cache-dir -e "/harm/tools/harm-coi[test]"
ENV PATH="/opt/harm-coi/bin:${PATH}"

WORKDIR /harm/build
RUN cmake -DCMAKE_BUILD_TYPE=Release -DHARM_COI_PYTHON=/opt/harm-coi/bin/python .. \
    && make -j"$(nproc)"
# the fast tests at build time (the slow ones: ctest -L slow)
RUN ctest -j"$(nproc)" -LE slow --output-on-failure

ENV PATH="/harm/build:${PATH}"
CMD ["bash"]
