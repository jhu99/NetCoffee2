#! /bin/bash
# test NetCoffee2 50 times with different alpha


for ((i = 1; i <= 50; i++))
do
   ./NetCoffee2 -inputnet ./testdata/test_sample/inputnet.txt -inputbit ./testdata/test_sample -output Res -numnet 3
done
