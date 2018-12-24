#!/bin/bash

# Set basic variables:
# Command name.
mode=$1

target_folder_name="target"

# Create target folder.
if [ ! -d ${target_folder_name} ]; then
    mkdir ${target_folder_name}
fi

echo -e "###########################################\n"

OPTIONS=""
# Execute commands:
if [ "$mode" == "seqn" ]; then

    echo "## Sequential mode."
    echo "## - drawing is disabled"
	echo -e "\n###########################################"

    OPTIONS+="-DOPT_SEQN=ON"

elif [ "$mode" == "openmp" ]; then

    echo "## Parallel mode using OpenMP."
    echo "## - drawing is disabled"
	echo -e "\n###########################################"

    OPTIONS+="-DOPT_OPEN_MP=ON"

elif [ "$mode" == "mpi" ]; then

    echo "## Parallel mode using MPI."
    echo "## - drawing is disabled"
    echo -e "\n###########################################"

    RUN_WITH_MPI=true
    OPTIONS+="-DOPT_MPI=ON"

elif [ "$mode" == "clean" ]; then

    echo "cleaning"
	echo -e "\n###########################################"

    rm -r "${target_folder_name}"
    exit 0

elif [ "$mode" == "default" ]; then

    echo "## Default sequential mode."
    echo "## - drawing is enabled"
	echo -e "\n###########################################"

    OPTIONS+="-DOPT_DRAWING=ON"

else

	echo -----------------  HELP  --------------------
	echo -- Chose one from the following command: --
	echo
	echo "--- #seqn         : Sequential mode"
	echo "--- #openmp       : parallelization using OpenMP"
	echo "--- #mpi          : parallelization using MPI"
    echo "--- #default      : default mode with drawing graphs"
    echo " "
    echo -e "After mode provide argument for program execution in specific mode\n"
    echo "In case of unexpected behaviour run clean"
	echo -e "\n###########################################"
	exit 1

fi

# Build
cmake ${OPTIONS} . -B"${target_folder_name}"/build
cmake --build "${target_folder_name}"/build

# Execute program
echo -e "\n\nExecute:\n\n"
if [ ${RUN_WITH_MPI} ]; then
    PROCESS_CNT=$2
    mpirun -np ${PROCESS_CNT} ./target/build/porr_dpso ${@:3}
else
    ./target/build/porr_dpso ${@:2}
fi