#!/usr/bin/env bash

set -e -o pipefail

DAY=$1

if [ -z "$DAY" ]; then
  echo "Must provide day"
  exit 1
fi

OUTPUT_DIR="src/day${DAY}"

mkdir ${OUTPUT_DIR}

touch ${OUTPUT_DIR}/input
touch ${OUTPUT_DIR}/debug

EXE_NAME=day${DAY}_1
SOURCE_FILE=${OUTPUT_DIR}/${EXE_NAME}.cpp
sed "s/<DAY>/${DAY}/g" src/template/day.cpp.template > ${SOURCE_FILE}

printf "\n\n# day %s\nadd_executable(%s %s)" "${DAY}" "${EXE_NAME}" "${SOURCE_FILE}" >> CMakeLists.txt
