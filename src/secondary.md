Secondary installer
=========

This runs in the gentoo system after initial installation.

installs:
- portage patches
- portage configs
- all desired packages

modifies:
- config files in /etc

and in the future it may restore backups for the /home directory, as well.