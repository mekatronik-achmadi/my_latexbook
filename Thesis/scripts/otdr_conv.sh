#!/bin/bash

for i in `ls *.sor`;do
	echo "converting $i"
	pyOTDR $i > /dev/null
done

echo "removing all JSON data"
rm -f *.json
