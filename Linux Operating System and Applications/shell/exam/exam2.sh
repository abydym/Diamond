#!/bin/bash
if [ $# -eq 0 ]
then
	ls .
else
	for i in "$@"
	do
		ls -l "$i" | grep '^d'
	done
fi
