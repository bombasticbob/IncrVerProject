# IncrVerProject

This is the home project for 'incrver', a simple application to
auto-increment and synchronize windows application/driver versions

USAGE:

From the command line:
<samp>
  INCRVER.EXE [-?|H|V:n.n.n.n|R:\"rcfilename\"] RC FILE NAME
   where  -? or -H displays this message
     and      -V:n.n.n.n sets the version string to 'n.n.n.n'
     and      -R:"rcfilename" extracts the version from "rcfilename"
              (in this case, 'rcfilename' must be quoted if it contains
               any 'white space' characters)
     and      RC FILE NAME represents the RC file name
              (in this case, the RC file name does not need to be quoted
               if it contains white space)
</samp>
The program will seek out the appropriate entries in an 'RC' file or a
device driver 'inf' file.  Either an 'inf' or 'RC' file may be specified
for either the target RC file name, or the file to extract the version from.

Sample usage:
<samp>
  incrver -V:1.2.3.4 myproject.rc
</samp>
This will assign the version '1.2.3.4' to the version resource in
'myproject.rc'.  Note that if there IS NO VERSION RESOURCE, the file will
not be modified.
<samp>
  incrver -R:driver.inf driver/driver.rc
</samp>
For a device driver project it will read the INF file 'driver.inf', and assign
a matching version number to the device driver's 'driver.rc' file.  This is
useful for when you want to deploy a device driver.
<samp>
  incrver driver.inf
  incrver project.rc
</samp>
This will increment the version specified in 'driver.inf' in the first command,
or in 'project.rc'.  The version is typically specified as '1.2.3.4' or as
'1, 2, 3, 4' (depending on which file and where it's being specified).  The
'incrver' reads the INF file's entries, or RC file entries, and attempts to
locate the correct one, THEN increments the last number in the sequence, and
re-writes it.

In the case of an 'INF' file, the current date is also written to the file.

A typical INF file would have an entry that looks like this under '[Version]':
<samp>
  Driverver = 05/10/2016,1.1.0.4
</samp>
'incrver' will update the '4' (making it a '5'), and change the date to today's
date.  (this helps make deploying the driver with a consistent version a bit
easier than it would have otherwise been, especially if you script this).

In the case of the RC file (which is typically a unicode file), you would have
a 'FILEVERSION' entry, and a 'PRODUCTVERSION' entry.  Both of these would have
the final number incremented.  The same would happen to the string resources
that are located later in the file.  No consistency checks are performed in
this case, but it allows you to specify different versions for FILEVERSION and
PRODUCTVERSION, in case you wanted to.

When you ASSIGN the version using /V or /R, both FILEVERSION and PRODUCTVERSION
and their associated string resources that follow will be assigned this same
version number.

