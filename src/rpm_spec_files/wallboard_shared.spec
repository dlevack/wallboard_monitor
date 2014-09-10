Name:           wallboard_shared
Version:        %{Version}
Release:        %{Release}
Summary:        Wallboard monitoring system shared library files
Vendor:         levack.net
Group:          mointoring
License:        GPL
URL:            https://github.com/dlevack/wallboard_monitor
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:	gcc-c++ >= 4.4

%description
This is the wallboard monitoring system shared library files.

%prep

%setup -q
%build
cd conf
make
cd ../db
make

%install
install -m 0755 -d $RPM_BUILD_ROOT/usr/lib64

install -m 0755 conf/libwallconf.so.1.0 $RPM_BUILD_ROOT/usr/lib64/libwallconf.so.1.0
install -m 0755 db/libwalldb.so.1.0 $RPM_BUILD_ROOT/usr/lib64/libwalldb.so.1.0

%clean
rm -rf $RPM_BUILD_ROOT

%post
cd /usr/lib64/
ln -sf libwallconf.so.1.0 libwallconf.so
ln -sf libwallconf.so.1.0 libwallconf.so.1
ln -sf libwalldb.so.1.0 libwalldb.so
ln -sf libwalldb.so.1.0 libwalldb.so.1

%postun
cd /usr/lib64/
rm -f libwallconf.so
rm -f libwallconf.so.1
rm -f libwalldb.so
rm -f libwalldb.so.1

%files
/usr/lib64/libwallconf.so.1.0
/usr/lib64/libwalldb.so.1.0

%defattr(-,root,root,-)
%doc



%changelog
