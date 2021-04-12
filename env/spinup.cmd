docker build env -t os

docker run --rm -it -v %cd%:/root/env os