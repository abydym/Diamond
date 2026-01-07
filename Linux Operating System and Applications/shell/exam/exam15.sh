#!/bin/bash

for ((i=100; i<=999; i++))
do
	((a = i /100))
	((b = i % 100 / 10))
	((c = i % 10))

	((sum = a*a*a + b*b*b + c*c*c))

	if((sum == i))
	then
		echo "$i is a Narcissistic number."
	fi
done
