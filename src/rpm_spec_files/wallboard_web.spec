Name:           wallboard_web
Version:        0.1
Release:        0.1
Summary:        Wallboard monitoring system web server files
Vendor:         levack.net
Group:          monitoring
License:        GPL
URL:            https://github.com/dlevack/wallboard_monitor
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArch:      noarch
Requires:	perl >= 5.0
Requires:	php >= 5.0
Requires:	php-mysql >= 5.0
Requires:	wallboard_core >= 0.1
Requires:	ImageMagick-perl

%description
This is the wallboard monitoring system web server files.

%prep
%setup -q
%build
%install
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/images
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/css
install -m 0755 -d $RPM_BUILD_ROOT/etc/httpd/conf.d
install -m 0755 -d $RPM_BUILD_ROOT/opt/wallboard_monitor/sbin
install -m 0644 apache_conf/wallboard_monitor.conf $RPM_BUILD_ROOT/etc/httpd/conf.d/wallboard_monitor.conf
install -m 0744 sbin/gen_wallboard_images.pl $RPM_BUILD_ROOT/opt/wallboard_monitor/sbin/gen_wallboard_images.pl
install -m 0644 css/wallboard.css $RPM_BUILD_ROOT/opt/wallboard_monitor/wallboard_web/css/wallboard.css
%clean
rm -rf $RPM_BUILD_ROOT

%post
/opt/wallboard_monitor/sbin/gen_wallboard_images.pl
/etc/init.d/httpd reload

%postun
/etc/init.d/httpd reload

%files
%dir /opt/wallboard_monitor/wallboard_web
%dir /opt/wallboard_monitor/wallboard_web/images
%dir /opt/wallboard_monitor/wallboard_web/css
/etc/httpd/conf.d/wallboard_monitor.conf
/opt/wallboard_monitor/sbin/gen_wallboard_images.pl
/opt/wallboard_monitor/wallboard_web/css/wallboard.css

%defattr(-,root,root,-)
%doc



%changelog
