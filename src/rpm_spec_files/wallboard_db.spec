Name:           wallboard_db
Version:        0.1
Release:        0.1
Summary:        Wallboard monitoring system database server files
Vendor:         levack.net
Group:          monitoring
License:        GPL
URL:            https://github.com/dlevack/wallboard_monitor
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:	php-mysql >= 5.0
Requires:	wallboard_core >= 0.1

%description
This is the wallboard monitoring system database server files.

%prep
%setup -q
%build
cd bin
make

%install
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/bin
install -m 0744 bin/install_db $RPM_BUILD_ROOT/opt/wallboard_monitor/bin/install_db

%clean
rm -rf $RPM_BUILD_ROOT

%post
echo "Run the /opt/wallboard_monitor/bin/install_db script to config database server."

%postun

%files
/opt/wallboard_monitor/bin/install_db

%defattr(-,root,root,-)
%doc



%changelog
