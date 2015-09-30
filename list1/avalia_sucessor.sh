#!/bin/bash
if [ "$1" = "" ] || [ "$2" = "" ] || [ "$3" = "" ]; then
  INPUT_FILE=./tests/assignmentExample
  POSITIONX=5
  POSITIONY=1
else
  INPUT_FILE=$1
  POSITIONX=$2
  POSITIONY=$3
fi

./avaliaSucessor $INPUT_FILE $POSITIONX $POSITIONY