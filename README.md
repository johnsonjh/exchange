# Exchange

Minimal CP/M for UNIX

### Overview

Greetings!

This is a utility that allows **CP/M** disk images to be manipulated under
UNIX. It supports disk images in either the standard *DRI* 8" SSSD format
or the *P112* 3.5" format. Disk images can be examined and files imported
and exported from them.

### Sources

The source is a slightly hacked over copy of **CP/M-68K** which has
been worked over to allow compilation on UNIX using GCC, to wit:

 - A handful of typecasts have been dropped in.
 - An assumption that an int is 16 bits has been fixed.
 - An assumption that chars are signed has been fixed.
 - The file `diverge.h` renames all of the globals to ensure they
   don't collide with operating system globals.
 - I changed the way the *BDOS* communicates with the *BIOS*; see
   `biosdef.h`
 - There are probably a couple of other minor changes I made that
   I've forgotten (perhaps renaming a routine or two before I
   decided to make `diverge.h`).
 - A **BIOS** that allows the program to be run under UNIX.

I've also added a couple of built-in commands:

 - *EXIT* causes **CP/M-68K** to exit, returning to the host operating
   system.
 - *IMPORT* copies a file from the current directory of the host
   operating system into the disk image.
 - *EXPORT* copies a file from the disk image into the current
   directory of the host operating system.

*IMPORT* and *EXPORT* do not accept wildcards.

This is just a quick hack that turned out to be useful, not a snazzy disk
image manipulation program.

### Building

To build the program, execute `make`. 

This results in an executable called `exchange`. 

The command-line syntax is: `exchange [-p112] file.img`, where:

* `-p112` This option tells the file to use the *P112* 3.5" disk format
  for the image. By default, the the standard *DRI* 8" SSSD format is used.

* `file.img` is the name of the disk image that should be used.

### Usage

In this example, I copy the file `BDOS.LST` from a *DRI* 8" SSSD image
containing **CP/M-80** 1.4 sources (obtained from
[The Unofficial CP/M Web Site](http://cpm.z80.de/)) to *USER 1* of the
*P112* boot disk image (obtained from
[The P112 Homepage](http://members.iinet.net.au/~daveb/p112/p112.html)):

```text
% uname -a
Linux powerpc.no.domain 2.4.22-2f #1 Sun Nov 9 16:49:49 EST 2003 ppc
% ls
bdosPLM.img  bootdisk.img  exchange
%./exchange bdosPLM.img

A>dir
A: BDOSI    SRC : BDOS     PLM : BDOS     OBJ : BDOS     LST 
A>export BDOS.LST
export BDOS    .LST -> BDOS.LST
A>exit
% ls
BDOS.LST  bdosPLM.img  bootdisk.img  exchange
%./exchange -p112 bootdisk.img

A>user 1

1A>dir
A: RECEIVE  PAS : UUENCODE PAS : UUDECODE PAS : USER     MAC : ROM    UUE 
A: ROM      PAS : ROM      COM 
1A>import bdos.lst
import BDOS.LST -> BDOS    .LST
1A>dir
A: RECEIVE  PAS : UUENCODE PAS : UUDECODE PAS : USER     MAC : ROM    UUE 
A: ROM      PAS : ROM      COM : BDOS     LST 
1A>exit
%
```

### Conclusion

Enjoy!

 - *Roger Ivie* \<anachronda@hotmail.com\>
