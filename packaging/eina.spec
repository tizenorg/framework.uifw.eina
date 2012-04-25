Name:       eina
Summary:    Data Type Library
Version:    1.2.0+svn.70441slp2+build01
Release:    1
Group:      System/Libraries
License:    LGPLv2
URL:        http://www.enlightenment.org/
Source0:    %{name}-%{version}.tar.gz
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


%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
%{_libdir}/libeina.so.*


%files devel
%defattr(-,root,root,-)
%{_includedir}/eina-1
%{_libdir}/*.so
%{_libdir}/pkgconfig/eina.pc
