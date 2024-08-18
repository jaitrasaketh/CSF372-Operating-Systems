#!/bin/bash
echo "In the forward order :"
for(( i=1;i<=100;i++))
do
   echo $i
done

echo "In the backward order :"
for(( i=100;i>=1;i--))
do
   echo $i
done 
