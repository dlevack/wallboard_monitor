Name:           wallboard_web
Version:        %{Version}
Release:        %{Release}
Summary:        Wallboard monitoring system web server files
Vendor:         levack.net
Group:          monitoring
License:        GPL
URL:            https://github.com/dlevack/wallboard_monitor
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:	php >= 5.0
Requires:	php-mysql >= 5.0
Requires:	wallboard_core >= %{Version}-%{Release}
Requires:	ImageMagick
Requires:	ImageMagick-c++

%description
This is the wallboard monitoring system web server files.

%prep
%setup -q
%build
cd bin
make

%install
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/images
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/css
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/admin
install -m 0755 -d $RPM_BUILD_ROOT/etc/httpd/conf.d
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/bin
install -m 0644 apache_conf/wallboard_monitor.conf $RPM_BUILD_ROOT/etc/httpd/conf.d/wallboard_monitor.conf
install -m 0644 css/wallboard.css $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/css/wallboard.css
install -m 0644 admin/index.php $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/admin/index.php
install -m 0644 admin/login.php $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/admin/login.php
install -m 0644 admin/login_process.php $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/admin/login_process.php
install -m 0644 admin/logout.php $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/admin/logout.php
install -m 0744 bin/gen_wallboard_images $RPM_BUILD_ROOT/opt/wallboard_monitor/bin/gen_wallboard_images

%clean
rm -rf $RPM_BUILD_ROOT

%post
/opt/wallboard_monitor/bin/gen_wallboard_images
/etc/init.d/httpd reload

%postun
/etc/init.d/httpd reload

%files
%dir /opt/wallboard_monitor/wallboard_web
%dir /opt/wallboard_monitor/wallboard_web/images
%dir /opt/wallboard_monitor/wallboard_web/css
%dir /opt/wallboard_monitor/wallboard_web/admin
/etc/httpd/conf.d/wallboard_monitor.conf
/opt/wallboard_monitor/bin/gen_wallboard_images
/opt/wallboard_monitor/wallboard_web/css/wallboard.css
/opt/wallboard_monitor/wallboard_web/admin/index.php
/opt/wallboard_monitor/wallboard_web/admin/login.php
/opt/wallboard_monitor/wallboard_web/admin/login_process.php
/opt/wallboard_monitor/wallboard_web/admin/logout.php

%defattr(-,root,root,-)
%doc



%changelog
