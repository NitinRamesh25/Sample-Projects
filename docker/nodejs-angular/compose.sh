#!/bin/bash

docker-compose build --no-cache --force-rm --compress --parallel
docker-compose up