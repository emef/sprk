Format:         1.0
Source:         sprk
Version:        0.1.0-1
Binary:         libsprk0, sprk-dev
Architecture:   any all
Maintainer:     John Doe <John.Doe@example.com>
Standards-Version: 3.9.5
Build-Depends: bison, debhelper (>= 8),
    pkg-config,
    automake,
    autoconf,
    libtool,
    libsodium-dev,
    libzmq4-dev,
    libczmq-dev,
    dh-autoreconf

Package-List:
 libsprk0 deb net optional arch=any
 sprk-dev deb libdevel optional arch=any

