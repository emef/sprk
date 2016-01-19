#
#    sprk - Project
#
#    Copyright (c) the Contributors as noted in the AUTHORS file.       
#    This file is part of CZMQ, the high-level C binding for 0MQ:       
#    http://czmq.zeromq.org.                                            
#                                                                       
#    This Source Code Form is subject to the terms of the Mozilla Public
#    License, v. 2.0. If a copy of the MPL was not distributed with this
#    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
#

Name:           sprk
Version:        0.1.0
Release:        1
Summary:        project
License:        MIT
URL:            http://example.com/
Source0:        %{name}-%{version}.tar.gz
Group:          System/Libraries
BuildRequires:  automake
BuildRequires:  autoconf
BuildRequires:  libtool
BuildRequires:  pkg-config
BuildRequires:  systemd-devel
BuildRequires:  libsodium-devel
BuildRequires:  zeromq-devel
BuildRequires:  czmq-devel
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
sprk project.

%package -n libsprk0
Group:          System/Libraries
Summary:        project

%description -n libsprk0
sprk project.
This package contains shared library.

%post -n libsprk0 -p /sbin/ldconfig
%postun -n libsprk0 -p /sbin/ldconfig

%files -n libsprk0
%defattr(-,root,root)
%doc COPYING
%{_libdir}/libsprk.so.*

%package devel
Summary:        project
Group:          System/Libraries
Requires:       libsprk0 = %{version}
Requires:       libsodium-devel
Requires:       zeromq-devel
Requires:       czmq-devel

%description devel
sprk project.
This package contains development files.

%files devel
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/libsprk.so
%{_libdir}/pkgconfig/libsprk.pc

%prep
%setup -q

%build
sh autogen.sh
%{configure} --with-systemd
make %{_smp_mflags}

%install
make install DESTDIR=%{buildroot} %{?_smp_mflags}

# remove static libraries
find %{buildroot} -name '*.a' | xargs rm -f
find %{buildroot} -name '*.la' | xargs rm -f


%changelog
