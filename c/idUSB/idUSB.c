#define _GNU_SOURCE

#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "idUSB.h"

static struct udev_device* get_child(struct udev* udev, struct udev_device* parent, const char* subsystem)
{
	struct udev_device* child = NULL;
	struct udev_enumerate *enumerate = udev_enumerate_new(udev);

	udev_enumerate_add_match_parent(enumerate, parent);
	udev_enumerate_add_match_subsystem(enumerate, subsystem);
	udev_enumerate_scan_devices(enumerate);

	struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
	struct udev_list_entry *entry;

	udev_list_entry_foreach(entry, devices) {
		const char *path = udev_list_entry_get_name(entry);
		child = udev_device_new_from_syspath(udev, path);
		break;
	}

	udev_enumerate_unref(enumerate);
	return child;
}

char* getTtyFromSerial(char* serial)
{
	if(!serial)
		return NULL;
	struct udev *udev = udev_new();

	struct udev_enumerate* enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "tty");
	udev_enumerate_scan_devices(enumerate);
	struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
	struct udev_list_entry *entry;

	char *ret = NULL;
	udev_list_entry_foreach(entry, devices) {
		const char *path = udev_list_entry_get_name(entry);
		struct udev_device *scsi = udev_device_new_from_syspath(udev, path);
		struct udev_device *block = get_child(udev, scsi, "block");
		struct udev_device *scsi_disk = get_child(udev, scsi, "scsi_disk");
		struct udev_device *usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");
		if(usb){
			if(!strcmp(serial, udev_device_get_sysattr_value(usb, "serial"))){
				char* tmp = strstr(path,"ttyUSB");
				if(tmp){
					//Found! Now lets extract ttyIDNO
					char c = tmp[6];
					if(asprintf(&ret,"/dev/ttyUSB%c",c))
				}
			}
		}
	}
	udev_enumerate_unref(enumerate);
	udev_unref(udev);
	return ret;
}
