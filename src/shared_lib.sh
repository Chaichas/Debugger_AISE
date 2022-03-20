#List of shared libraries
echo "***********************   Loaded Shared Libraries:   ***********************"
echo ""
echo "******************* Entire Dependencies of Executable: *********************"
ldd /bin/ls
echo ""

echo "******************* Direct Dependencies of Executable: *********************"
objdump -p prog_loop | grep NEEDED
echo "****************************************************************************"
