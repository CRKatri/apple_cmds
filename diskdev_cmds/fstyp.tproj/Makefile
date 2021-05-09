all:
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_msdos MAN=fstyp_msdos.8 all)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_ntfs MAN=fstyp_ntfs.8 all)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_udf MAN=fstyp_udf.8 all)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp MAN=fstyp.8 all)

clean:
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_msdos MAN=fstyp_msdos.8 clean)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_ntfs MAN=fstyp_ntfs.8 clean)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_udf MAN=fstyp_udf.8 clean)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp MAN=fstyp.8 clean)

install:
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_msdos MAN=fstyp_msdos.8 install)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_ntfs MAN=fstyp_ntfs.8 install)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp_udf MAN=fstyp_udf.8 install)
	(${MAKE} ${.MAKEFLAGS} -f progs.mk PROG=fstyp MAN=fstyp.8 install)

.PHONY: all clean install
