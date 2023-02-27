#!/usr/bin/env bash

cd build;
cmake ..;
make;
cp plainman ..;
cd ..;
./plainman;
