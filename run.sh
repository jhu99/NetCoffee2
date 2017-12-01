#! /bin/bash
# test NetCoffee2 50 times with different alpha


for ((i = 1; i <= 50; i++))
do
	echo “./NetCoffee2 -input_net ./testdata/test2/int_net_test2.txt -input_bit ./testdata/test2/int_bit_test2.txt -output "alignmentResule_alph$i.txt" -numnet 3“
done
