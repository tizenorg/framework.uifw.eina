Name:       eina
Summary:    Data Type Library
Version:    1.7.1+svn.77445+build35
Release:    1
Group:      System/Libraries
License:    LGPL-2.1+
URL:        http://www.enlightenment.org/
Source0:    %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(dlog)


%description
Enlightenment Foundation Library providing optimized data types Eina is a multi-platform library that provides optimized data types and a few
 tools. It supports the following data types:
  o Array
  o Hash Table
  o Double-linked list
  o Red-black tree
  o Shared string
  o Access Content types
    + Accessor: can access items of a container randomly
    + Iterator: can access items of a container sequentially


%package devel
Summary:    Data Type Library (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}


%description devel
Enlightenment Foundation Library providing optimized data types (devel)

%package tools
Summary:    Enlightenment Foundation Library providing optimized data types (tools)
Group:      Development/Tools
Requires:   %{name} = %{version}-%{release}
Provides:   %{name}-bin
Obsoletes:  %{name}-bin

%description tools
Enlightenment Foundation Library providing optimized data types (tools)


%prep
%setup -q


%build
export CFLAGS+=" -fvisibility=hidden -fPIC -Wall"
export LDFLAGS+=" -fvisibility=hidden -Wl,--hash-style=both -Wl,--as-needed"

%autogen --disable-static\
         --enable-magic-debug

make %{?jobs:-j%jobs}


%install
%make_install
mkdir -p %{buildroot}/%{_datadir}/license
cp %{_builddir}/%{buildsubdir}/COPYING %{buildroot}/%{_datadir}/license/%{name}
cp %{_builddir}/%{buildsubdir}/COPYING %{buildroot}/%{_datadir}/license/%{name}-tools


%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%{_libdir}/libeina.so.*
%{_datadir}/license/%{name}
%manifest %{name}.manifest


%files devel
%defattr(-,root,root,-)
%{_includedir}/eina-1
%{_libdir}/*.so
%{_libdir}/pkgconfig/eina.pc


%files tools
%defattr(-,root,root,-)
%{_bindir}/*
%{_datadir}/license/%{name}-tools
%manifest %{name}-tools.manifest
