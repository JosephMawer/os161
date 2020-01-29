os161 - getting set up with os161

## INSTALL WSL
https://docs.microsoft.com/en-us/windows/wsl/install-win10?redirectedfrom=MSDN

## OS161 RESOURCES
http://os161.eecs.harvard.edu/resources/building.html


1) Install the toolchain: https://www.ops-class.org/asst/setup/

sudo add-apt-repository ppa:ops-class/os161-toolchain
sudo apt-get update
sudo apt-get install os161-toolchain



2) Run the configuration setting the ostree path
./configure --ostree=/mnt/c/users/joseph.mawer.IDEA/ubuntu/os161/root


3) Configure the kernel
goto: /kern/conf
run:  ./config DUMBVM

4) Build the kernel

goto: /kern/compile/DUMBVM

run: bmake depend	// to build dependencies
run: bmake		// to build kernel
run  bmake install	// to publish kernel to the ostree path set above

5) use sys161 to run the built kernel
 
goto: /os161/root
run:  sys161 kernel

* sys161 file needs to be installed in this directory in order to run the kernel
 
  http://os161.eecs.harvard.edu/
  http://os161.eecs.harvard.edu/documentation/sys161-2.0.8/

- sys161 is a system simulator
- sys161 requires the sys161.conf file to be in the directory you run it
- sys161 configures the virtual machine that your kernel runs in, i.e. it
confiures the system simulator

run: sys161 kernel	// boots the kernel
