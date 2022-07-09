// all the stuff an installer needs
struct InstData {
	// NOTE: bootloader is always installed to /dev/sda and /dev/nvme0n1
	char const* os_part_path; // /dev/bla
	char const* home_part_uuid;
	char const* home_part_fstype;
	char const* swap_part_uuid;
	char const* make_conf;
};

InstData data_games = {
	"/dev/nvme0n1p2",
	"9747e99a-603d-4602-b71d-052799fd47cb",
	"btrfs",
	nullptr,
	// TODO: read /etc/portage/make.conf at build time?
	// TODO
};

/*
pub let data_work = InstData {
	// TODO
}

pub let data_x240 = InstData {
	// TODO
}

pub let data_w500 = InstData {
	// TODO
}
*/

void shell(char const* run)
{
	assert(system(run));
}