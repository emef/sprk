#
#    sprk - Project
#
#    The MIT License (MIT)                                                         
#                                                                                  
#    Copyright (c) 2016 Matt Forbes                                                
#                                                                                  
#    Permission is hereby granted, free of charge, to any person obtaining a copy  
#    of this software and associated documentation files (the "Software"), to deal 
#    in the Software without restriction, including without limitation the rights  
#    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
#    copies of the Software, and to permit persons to whom the Software is         
#    furnished to do so, subject to the following conditions:                      
#                                                                                  
#    The above copyright notice and this permission notice shall be included in all
#    copies or substantial portions of the Software.                               
#                                                                                  
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
#    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
#    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
#    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
#    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
#    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
#    SOFTWARE.                                                                     
#

Name:           sprk
Version:        0.0.0
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

%files
%defattr(-,root,root)
%doc README.md
%{_bindir}/sprk_broker
%{_bindir}/sprk_executor
%{_bindir}/inprocess
%{_bindir}/outprocess
%{_bindir}/gendata
%{_bindir}/topology


%changelog
