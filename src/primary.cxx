void prepare() {
	shell("mkdir -p /mnt/home");
	shell("mkdir -p /mnt/gentoo");
	// TODO: shell("mount /home to /mnt/home");

	// TODO: reformat / as ext4
	// TODO shell("mkfs.ext4 ")

	// TODO: mount / to /mnt/gentoo

	shell("cd /mnt/gentoo && tar xpf /stage3.tar.xz --xattrs-include='*.*' --numeric-owner");

	shell("cp -rf /portage /mnt/gentoo/etc");

	shell("cp --dereference /etc/resolv.conf /mnt/gentoo/etc/");

	shell("mount --types proc /proc /mnt/gentoo/proc");

	// TODO: select portage profile as a recent desktop/systemd profile (preferably without plasma or much else that takes ages to build)

	shell("mount --rbind /sys /mnt/gentoo/sys");
	shell("mount --make-rslave /mnt/gentoo/sys");

	shell("mount --rbind /dev /mnt/gentoo/dev");
	shell("mount --make-rslave /mnt/gentoo/dev");

	shell("mount --bind /run /mnt/gentoo/run");
	shell("mount --make-slave /mnt/gentoo/run");
}

void primary(bool keep_previous_passwords = false) {
	std::string root_password = "";
	std::string user_password = "";
	static char buf[257];
	memset(buf, 0, 257);

	if (!keep_previous_passwords) {
		// interactively ask for the following:
		// -> root password (if requested to set/unset, and not reusing previous one)
		puts("Please enter a root password.");
		assert(fgets(buf, 256, stdin));
		root_password = buf;
		memset(buf, 0, 257);

		// -> user password (see above)
		puts("Please enter a user password.");
		assert(fgets(buf, 256, stdin));
		user_password = buf;
		memset(buf, 0, 257);
	}

	shell("emerge-webrsync");

	// TODO
}