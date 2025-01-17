#!/bin/bash

script_dir="$(dirname $(readlink -e $0))"

BATCH_ARGS=("--simulate" "-O0" "-fwhole-program" "--clock-period=15" "-D'printf(fmt, ...)='" "--channels-type=MEM_ACC_NN" "--experimental-setup=BAMBU")
OUT_SUFFIX="all_gcc_CHStone-frontend"
BENCHMARKS_ROOT="${script_dir}/../../examples/CHStone/CHStone"

python3 $script_dir/../../etc/scripts/test_panda.py --tool=bambu \
   --args="--configuration-name=GCC49-O0-wp-NN --compiler=I386_GCC49 ${BATCH_ARGS[*]}" \
   --args="--configuration-name=GCC5-O0-wp-NN  --compiler=I386_GCC5  ${BATCH_ARGS[*]}" \
   --args="--configuration-name=GCC6-O0-wp-NN  --compiler=I386_GCC6  ${BATCH_ARGS[*]}" \
   --args="--configuration-name=GCC7-O0-wp-NN  --compiler=I386_GCC7  ${BATCH_ARGS[*]}" \
   --args="--configuration-name=GCC8-O0-wp-NN  --compiler=I386_GCC8  ${BATCH_ARGS[*]}" \
   -l${BENCHMARKS_ROOT}/../chstone_list \
   -o "out_${OUT_SUFFIX}" -b${BENCHMARKS_ROOT} \
   --name="${OUT_SUFFIX}" "$@"
