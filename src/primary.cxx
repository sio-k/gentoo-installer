void prepare(InstData* id, bool keep_previous_passwords = false) {
	shell("mkdir -p /mnt/gentoo");

	// TODO: mount os part
	if (keep_previous_passwords) {
		// TODO: save /etc/passwd and /etc/shadow
	}

	// TODO: save other bits we want to save
	// TODO: just save the entire portage config?

	shell(
		( String("mkfs.ext4 ")
		+ String(id->os_part_path)
		).c_str()
	)

	shell(
		( String("mount ")
		+ String(os_part_path)
		+ " /mnt/gentoo"
		).c_str()
	)

	shell("cd /mnt/gentoo && tar xpf /stage3.tar.xz --xattrs-include='*.*' --numeric-owner");

	// apply portage config
	shell("cp -rf /portage /mnt/gentoo/etc");

	if (keep_previous_passwords) {
		// TODO: reapply saved /etc/passwd and /etc/shadow
	}

	// TODO: apply other saved bits

	// mount /home
	shell(
		( String("mount ")
		+ String(id->home_part_path)
		+ String(" /mnt/gentoo/home")
		).c_str()
	);

	shell("cp --dereference /etc/resolv.conf /mnt/gentoo/etc/");

	shell("mount --types proc /proc /mnt/gentoo/proc");

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

	// TODO: apply entire /etc/ config NOW
	// TODO: apply all user config stuff NOW

	shell("emerge-webrsync");

	// select portage profile as a recent desktop/systemd profile (preferably without plasma or much else that takes ages to build)
	shell("cd /etc/portage && rm make.profile && ln -s /var/db/repos/gentoo/profiles/default/linux/amd64/17.1/desktop/systemd make.profile");
	// TODO: don't hardcode gentoo profile version, determine dynamically instead


	shell("emerge --ask --verbose --update --deep --newuse @world");
	// TODO: autoaccept unmasks; don't prompt

	// TODO
}