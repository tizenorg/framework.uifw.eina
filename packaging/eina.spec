Name:       eina
Summary:    Data Type Library
Version:    1.7.1+svn.77445+build06r01
Release:    1
Group:      System/Libraries
License:    LGPLv2
URL:        http://www.enlightenment.org/
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  pkgconfig(dlog)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig


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
export CFLAGS+=" -fvisibility=hidden"
export LDFLAGS+=" -fvisibility=hidden"

%autogen --disable-static
%configure --disable-static \
    --disable-rpath --enable-static-chained-pool --enable-magic-debug

make %{?jobs:-j%jobs}


%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license
cp %{_builddir}/%{buildsubdir}/COPYING %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%{_libdir}/libeina.so.*
%manifest %{name}.manifest
/usr/share/license/%{name}
%manifest %{name}.manifest


%files devel
%defattr(-,root,root,-)
%{_includedir}/eina-1
%{_libdir}/*.so
%{_libdir}/pkgconfig/eina.pc

%files tools
%defattr(-,root,root,-)
%{_bindir}/*
