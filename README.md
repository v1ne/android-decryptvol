# Description

Ever got your display broken or had a backup of you Android's block devices 
and needed access to your files?
Oh, of course, you enabled Android's device encryption...

With this tool, you can easily decrypt the block device on your PC.

# Build

You need to have at least the Linux headers installed, adjust the Makefile.

```$ gmake```

Now, you built `android-decryptvol`.

# Usage

Assuming, your encrypted partition is `$file` and your password is `p4ssw0rd`,
this command mounts it at `/mnt/somewhere`:

```
# losetup -f --show $file
	loop0
# android-decryptvol /dev/loop0 /mnt/somewhere p4ssw0rd
```

The program will tell you if something went wrong, e.g. you used the wrong
password.

Then, copy your data and unmount the image:

```
# umount /mnt/somewhere
# dmsetup remove AndroidData
# losetup -d loop0
```
