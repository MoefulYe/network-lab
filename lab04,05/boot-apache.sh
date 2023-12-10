#! /bin/sh
docker run -d \
  --name lab-apache \
  -p 8080:80 \
  -v ${PWD}/static:/usr/local/apache2/htdocs/ \
  httpd:alpine
