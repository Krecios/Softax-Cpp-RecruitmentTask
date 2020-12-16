FROM ubuntu:18.04

RUN apt-get -y update && apt-get -y install build-essential && apt-get -y install nlohmann-json-dev && apt-get -y install python 
COPY . /usr/src/softax
WORKDIR /usr/src/softax
EXPOSE 9000
RUN make
CMD ["./softax.o"]