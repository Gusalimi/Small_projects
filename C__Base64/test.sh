#!/bin/bash

echo 'Compiling'
make re > /dev/null
echo 'Original message:' $1
echo 'Encoded message:' $(echo -n $1 | base64)
echo -n $1 | base64 | ./ft_base64 -d
