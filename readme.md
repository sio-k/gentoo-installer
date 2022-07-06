automagic gentoo installation
========

idea
-----

Gentoo is installed from a different distro incarnation using Ansible via SSH to configure and install it.

Options for diff. distro:
- separate debian stable that has sshd, can mount /home (btrfs?), and has python on it. That's more or less all there is to it.
- A/B systems, installation from the currently "good" system
- tiny debian with sshd + A/B

theory of it: see gentoo install alternatives: installing from an existing linux distro

theoretical way of doing things
-----------

1. boot into separate tiny debian on a small extra partition
2. mount /home into /mnt/home
3. run installer script from installer directory in /mnt/home, which does:
	1. pave over the OS partition (reformat)
	2. std. gentoo install stuff (incl. setting up fstab with /home being properly mounted)
	3. make sure to configure sshd
	4. make sure to have new user have correct uid so /home doesn't have to be fucked with
	5. set up all users and passwords
	6. reboot into the new system
4. run secondary installer script in /home:
	1. install all portage patches, configs etc.
	2. install all desired packages
	3. pave over all configs in root in desired way
5. reboot into debian
6. write out new system image using dd to /home/data/sysimgs/new_image
7. deploy system image using ansible while booted into tiny debian

installer scripts are separated by host, all sitting in a single git repo

- basic thing doesn't have to be a shellscript, could be a C++ program with proper error handling and error reporting?
- secondary could be a C++ program?