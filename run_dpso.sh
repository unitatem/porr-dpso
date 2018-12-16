#!/bin/bash

# Set basic variables:
# Command name.
input=$1

target_folder_name="target"

# Create basic target folder.
if [ ! -d $target_folder_name ]; then
    mkdir $target_folder_name
fi

   	echo "###########################################"
    echo " "

# Execute commands:
if [ "$input" == "seqn" ]; then

    echo "## Sequential mode."
    echo "## - drawing is disabled"
    echo
	echo "###########################################" 

    # Create build and binary files
    cmake -DMODE="SEQN" -DDRAWING="FALSE" . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build 

elif [ "$input" == "pararell" ]; then   

    echo "## Pararell mode using OpenMP."
    echo "## - drawing is disabled"
    echo 
	echo "###########################################"

    # Create build and binary files
    cmake -DMODE="PARARELL" -DDRAWING="FALSE" . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build 

elif [ "$input" == "clean" ]; then
    rm -r "${target_folder_name}"/

elif [ "$input" == "help" ]; then

	echo -----------------  HELP  --------------------
	echo -- Chose one from the following command: --
	echo 
	echo " --- #seqn         : Sequential mode" 
	echo " --- #pararell     : pararellisation using OpenMP"
    echo " --- #without arg  : default mode with drawing graphs"
	echo 
	echo "###########################################"

else

    echo "## Default sequential mode."
    echo "## - drawing is enabled"
    echo 
	echo "###########################################"
    # Create build and binary files
    cmake -DMODE="DEFAULT" -DDRAWING="TRUE" . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build
fi
