/*
    libparted - a library for manipulating disk partitions
    Copyright (C) 2000 Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <config.h>

#include <parted/parted.h>
#include <parted/endian.h>

#if ENABLE_NLS
#  include <libintl.h>
#  define _(String) dgettext (PACKAGE, String)
#else
#  define _(String) (String)
#endif /* ENABLE_NLS */

#include <unistd.h>
#include <string.h>

static PedGeometry*
reiser4_probe (PedGeometry* geom)
{
	char	buf[512];

	if (!ped_geometry_read (geom, buf, 128, 1))
		return 0;	
	
	if ( strcmp( buf, "ReIsEr4" ) == 0 )
		return ped_geometry_duplicate( geom ) ;

	else
		return NULL;
}

static PedFileSystemOps reiser4_ops = {
	probe:		reiser4_probe,
};

static PedFileSystemType reiser4_type = {
	next:	NULL,
	ops:	&reiser4_ops,
	name:	"reiser4"
};

void
ped_file_system_reiser4_init ()
{
	ped_file_system_type_register (&reiser4_type);
}

void
ped_file_system_reiser4_done ()
{
	ped_file_system_type_unregister (&reiser4_type);
}

