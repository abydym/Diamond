#!/bin/bash
mkdir -p backup
for file in *.txt
do
	mv "$file" backup/
	chmod 600 "backup/$file"
done
