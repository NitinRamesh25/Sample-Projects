#!/bin/bash

docker-compose build --compress --force-rm --parallel --no-cache
docker-compose up