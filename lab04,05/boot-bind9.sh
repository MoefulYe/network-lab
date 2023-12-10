#! /bin/sh
docker run -d \
-p 53:53/udp \
-p 53:53/tcp \
-e BIND9_USER=root \
-v ${PWD}/bind/named.conf:/etc/bind/named.conf \
-v ${PWD}/bind/example.com:/etc/bind/example.com \
--name lab-bind9 \
ubuntu/bind9:latest
