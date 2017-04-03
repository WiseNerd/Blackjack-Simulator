#!/bin/bash

echo "How many pies do you want to eat?"
echo ">"

read pynum

echo "How many decks do you like in your pies"
echo ">"

read decks

COUNTER=0
while [ $COUNTER -lt $pynum ]; do
        python /Users/AstralPiper/Desktop/food_for_the_head/Machines/playtime/BJ.py $decks &
        let COUNTER=COUNTER+1
done

