#!/bin/bash

script_dir="$(dirname $(readlink -e $0))"
ggo_require_compiler=1
. $script_dir/generic_getopt.sh

BATCH_ARGS=("--simulate" "-O3" "-fwhole-program" "--experimental-setup=BAMBU" "--clock-period=15" "-D'printf(fmt, ...)='")
OUT_SUFFIX="${compiler}_CHStone-memarch1"
BENCHMARKS_ROOT="${script_dir}/../../examples/CHStone/CHStone"

python3 $script_dir/../../etc/scripts/test_panda.py --tool=bambu \
   --args="--configuration-name=${compiler}-O3-wp-11-D00-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D00 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-N1-D00-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D00 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-NN-D00-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D00 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-11-D10-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D10 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-N1-D10-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D10 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-NN-D10-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D10 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-11-D11-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D11 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-N1-D11-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D11 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-NN-D11-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D11 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-11-D21-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D21 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-N1-D21-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D21 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-NN-D21-EXT --memory-allocation-policy=EXT_PIPELINED_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D21 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-11-D00-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D00 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-N1-D00-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D00 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-NN-D00-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D00 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-11-D10-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D10 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-N1-D10-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D10 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-NN-D10-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D10 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-11-D11-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D11 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-N1-D11-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D11 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-NN-D11-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D11 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-11-D21-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_11 --memory-ctrl-type=D21 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-N1-D21-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_N1 --memory-ctrl-type=D21 ${BATCH_ARGS[*]}"\
   --args="--configuration-name=${compiler}-O3-wp-VVD-NN-D21-NO-BRAM --memory-allocation-policy=NO_BRAM --channels-type=MEM_ACC_NN --memory-ctrl-type=D21 ${BATCH_ARGS[*]}"\
   -l${script_dir}/chstone_memarch_list1 \
   -o "out_${OUT_SUFFIX}" -b${BENCHMARKS_ROOT} \
   --name="${OUT_SUFFIX}" $ARGS
