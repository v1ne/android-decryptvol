/*
 * Copyright (C) 2014 v1ne <v1ne2go@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#define _BSD_SOURCE

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "fs_mgr.h"
#include "cryptfs.h"

char* devname;
char *dmvolname="AndroidData";

int main(int argc, char* argv[]) {
	char path[MAXPATHLEN];
	int new_maj, new_min;


	if(argc < 4) {
		printf("Usage: %s device mountPoint Password\n%s", argv[0],
		"\tdevice: path to the device to decrypt\n"
		"\tmountPoint: where to mount the decrypted filesystem\n"
		"\tPassword: The password used for decryption\n\n"
		"This program uses Android's vold code to decrypt an encrypted Android\n"
		"data volume. Based on code by the Android Open Source Project,\n"
		"Todd C. Miller, Colin Percival. Frontend by v1ne.\n");
		exit(1);
	}

	devname = argv[1];
	char *mountpoint = argv[2];
	char *pw = argv[3];

	struct stat devstat;
	if(stat(devname, &devstat)) {
		perror("Unable to stat, invalid path? Error:");
		exit(1);
	}

	if(cryptfs_setup_volume(dmvolname, devname,
		path, sizeof(path), &new_maj, &new_min)) {
		fprintf(stderr,	"Unable to decrypt %s\n", "TODO");
		release_dm_dev(dmvolname);
		exit(1);
	}

	if(test_mount_encrypted_fs(pw, mountpoint, dmvolname)) {
		printf("Mount failed, wrong password?\n");
		return 1;
	}

	printf("Successfully mounted volume %s at %s\n", dmvolname, mountpoint);
	printf("Use \"dmsetup remove %s\" to release the encrypted device\n", dmvolname);


	return 0;
}

struct fstab fstab = {};
int fs_mgr_get_crypt_info(struct fstab *fstab, char *key_loc, char *real_blkdev, int size) {
	strcpy(real_blkdev, devname);
	return 0;
}
