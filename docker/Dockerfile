FROM ubuntu:24.04

# Update Ubuntu Software repository
RUN apt update

ARG DEBIAN_FRONTEND=noninteractive
RUN apt install -y git
RUN git clone https://github.com/SamueleGerminiani/harm.git
RUN apt-get install -y uuid-dev pkg-config
RUN apt install -y build-essential

RUN apt install -y wget unzip python3 python3-dev
ENV PYTHON=python3

#no cache from here
ARG CACHE_DATE=not_a_date

RUN wget -q https://github.com/Kitware/CMake/releases/download/v3.31.1/cmake-3.31.1-linux-x86_64.sh -O cmake.sh \
    && chmod +x cmake.sh \
    && ./cmake.sh --prefix=/usr/local --exclude-subdir --skip-license \
    && rm cmake.sh

WORKDIR "/harm/third_party"
RUN sh ./install_all.sh


WORKDIR "/harm"
RUN git reset --hard
RUN git pull
RUN mkdir build
WORKDIR "/harm/build"
RUN cmake -DCMAKE_BUILD_TYPE=Release ..
RUN make -j16





# run the command
CMD ["bash"]

