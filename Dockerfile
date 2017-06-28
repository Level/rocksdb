FROM node:7

RUN npm i node-gyp -g
RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app
COPY . /usr/src/app
RUN npm install
RUN node-gyp configure
RUN node-gyp build
RUN npm test
