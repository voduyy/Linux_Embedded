cmd_/home/voduy/Workspace/Linux_Embedded/Linux_Kernel_Programming/lesson1_character_device_driver/05_file_rw/Module.symvers := sed 's/\.ko$$/\.o/' /home/voduy/Workspace/Linux_Embedded/Linux_Kernel_Programming/lesson1_character_device_driver/05_file_rw/modules.order | scripts/mod/modpost -m -a  -o /home/voduy/Workspace/Linux_Embedded/Linux_Kernel_Programming/lesson1_character_device_driver/05_file_rw/Module.symvers -e -i Module.symvers   -T -