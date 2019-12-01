#!/bin/bash

U='
0.1
0.2
0.3
0.4
0.5
0.6
0.7
0.8
0.9
1.0
1.1
1.2
1.3
1.4
1.5
1.6
1.7
1.8
1.9
2.0'

P='
10
20
30
40
50
60
70
80
90
100
110
120
130
140
150
160
170
180
190
200'

for u in $U; do
    rm -rf ../$u
    mkdir -p ../$u
    for p in $P; do
        mkdir -p ../$u/$p
        cp -r * ../$u/$p/
        (
            echo "Simulate for U=$u, P=$p"
            cd ../$u/$p
            sed -i "19s/20/$p/;23s/0.3/$u/" constant/laserProperties
            ./Allrun
        )
    done
done
