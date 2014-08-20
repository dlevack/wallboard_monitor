Name:           wallboard_core
Version:        0.1
Release:        0.1
Summary:        Wallboard monitoring system core files
Vendor:         levack.net
Group:          mointoring
License:        GPL
URL:            https://github.com/dlevack/wallboard_monitor
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArch:      noarch
Requires:	perl >= 5.0
Requires:	php >= 5.0
Requires:	php-mysql >= 5.0

%description
This is the wallboard monitoring system core files.

%prep
%setup -q
%build
%install
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/include_files
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/conf_files
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/sbin
install -m 0755 -d $RPM_BUILD_ROOT/usr/share/perl5/Wallboard
install -m 0644 include_files/auth.php $RPM_BUILD_ROOT/opt/wallboard_monitor/include_files/auth.php
install -m 0644 include_files/colors.php $RPM_BUILD_ROOT/opt/wallboard_monitor/include_files/colors.php
install -m 0644 include_files/db.php $RPM_BUILD_ROOT/opt/wallboard_monitor/include_files/db.php
install -m 0644 include_files/ini_files.php $RPM_BUILD_ROOT/opt/wallboard_monitor/include_files/ini_files.php
install -m 0744 sbin/db_config.php $RPM_BUILD_ROOT/opt/wallboard_monitor/sbin/db_config.php
install -m 0644 include_files/Wallboard/DB.pm $RPM_BUILD_ROOT/usr/share/perl5/Wallboard/DB.pm
install -m 0644 conf_files/db.conf $RPM_BUILD_ROOT/opt/wallboard_monitor/conf_files/db.conf
install -m 0644 include_files/web.php $RPM_BUILD_ROOT/opt/wallboard_monitor/include_files/web.php

%clean
rm -rf $RPM_BUILD_ROOT

%post
echo "Please run /opt/wallboard_monitor/sbin/db_config.php to verify database config"

%files
%dir /opt/wallboard_monitor
%dir /opt/wallboard_monitor/include_files
%dir /opt/wallboard_monitor/conf_files
%dir /opt/wallboard_monitor/sbin
/opt/wallboard_monitor/include_files/auth.php
/opt/wallboard_monitor/include_files/colors.php
/opt/wallboard_monitor/include_files/db.php
/opt/wallboard_monitor/include_files/ini_files.php
/opt/wallboard_monitor/sbin/db_config.php
/usr/share/perl5/Wallboard/DB.pm
/opt/wallboard_monitor/conf_files/db.conf
/opt/wallboard_monitor/include_files/web.php

%defattr(-,root,root,-)
%doc



%changelog
