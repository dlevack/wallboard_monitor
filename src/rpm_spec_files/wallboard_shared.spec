Name:           wallboard_shared
Version:        0.1
Release:        0.1
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

%install
install -m 0755 -d $RPM_BUILD_ROOT/usr/lib64

install -m 0755 conf/libwallconf.so.1.0 $RPM_BUILD_ROOT/usr/lib64/libwallconf.so.1.0

%clean
rm -rf $RPM_BUILD_ROOT

%post
cd /usr/lib64/
ln -sf libwallconf.so.1.0 libwallconf.so
ln -sf libwallconf.so.1.0 libwallconf.so.1

%files
/usr/lib64/libwallconf.so.1.0

%defattr(-,root,root,-)
%doc



%changelog
