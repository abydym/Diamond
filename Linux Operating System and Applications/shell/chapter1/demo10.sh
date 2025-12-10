#!/bin/bash

String=abcABC123ABCabc
echo ${String#a*C}      # 123ABCabc

echo ${String##a*C}     # abc


String=abcABC123ABCabc
echo ${String%b*c}      # abcABC123ABCa

echo ${String%%b*c}     # a
