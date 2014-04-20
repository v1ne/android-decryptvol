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

`android-decryptvol device mountpoint password`

If you have a file, run losetup -f --show $file to create a block device from 
it, e.g. /dev/loop0. Else, supply the block device.
The tool tries to mount your filesystem to check if the decryption succeeded,
so supply a directory as mount point.
Also, supply the right password. ;-) Using a wrong password will result in a 
message.
