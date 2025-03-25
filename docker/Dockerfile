#Download base image ubuntu 23.04
FROM ubuntu:22.04
# Update Ubuntu Software repository
RUN apt update

ARG DEBIAN_FRONTEND=noninteractive
RUN apt install -y git
RUN git clone https://github.com/SamueleGerminiani/harm.git
RUN apt-get install -y uuid-dev pkg-config
RUN apt install -y build-essential
RUN apt install -y wget unzip cmake python3 python3-distutils python3-apt
ENV PYTHON=python3
WORKDIR "/harm/third_party"
RUN sh ./install_all.sh

#no cache from here
ARG CACHE_DATE=not_a_date
WORKDIR "/harm"
RUN git reset --hard
RUN git pull
RUN mkdir build
WORKDIR "/harm/build"
RUN cmake -DCMAKE_BUILD_TYPE=Release ..
RUN make -j16





# run the command
CMD ["bash"]

