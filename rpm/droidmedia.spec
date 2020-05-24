%define strip /bin/true
%define __requires_exclude  ^.*$
%define __find_requires     %{nil}
%global debug_package       %{nil}
%define __provides_exclude_from ^.*$

%define _target_cpu %{device_rpm_architecture_string}

Name:          droidmedia
Summary:       Android media wrapper library
Version:       0.20170214.0
Release:       1
Group:         System/Libraries
License:       ASL 2.0
BuildRequires: ubu-trusty
BuildRequires: sudo-for-abuild
BuildRequires: droid-bin-src-full
Source0:       %{name}-%{version}.tgz
AutoReqProv:   no

%description
%{summary}

%package       devel
Summary:       droidmedia development headers
Requires:      droidmedia = %{version}-%{release}
BuildArch:     noarch

%description   devel
%{summary}

%prep

%if %{?device_rpm_architecture_string:0}%{!?device_rpm_architecture_string:1}
echo "device_rpm_architecture_string is not defined"
exit -1
%endif

%setup -T -c -n droidmedia
sudo chown -R abuild:abuild /home/abuild/src/droid/
mv /home/abuild/src/droid/* .
mkdir -p external
pushd external
tar -zxf %SOURCE0
mv droidmedia* droidmedia
popd

cat /dev/null > external/droidmedia/env.mk

%if %{?force_hal:1}%{!?force_hal:0}
echo Forcing Camera HAL connect version %{force_hal}
echo FORCE_HAL := %{force_hal} >> external/droidmedia/env.mk
%endif

%build
echo "building for %{device_rpm_architecture_string}"
TARGETS=`external/droidmedia/detect_build_targets.sh %{device_rpm_architecture_string} || exit 1`
droid-make %{?_smp_mflags} $TARGETS

%install

if [ -f out/target/product/*/system/lib64/libdroidmedia.so ]; then
DROIDLIB=lib64
else
DROIDLIB=lib
fi

mkdir -p $RPM_BUILD_ROOT/%{_libexecdir}/droid-hybris/system/$DROIDLIB/
mkdir -p $RPM_BUILD_ROOT/%{_libexecdir}/droid-hybris/system/bin/
mkdir -p $RPM_BUILD_ROOT/%{_includedir}/droidmedia/
mkdir -p $RPM_BUILD_ROOT/%{_datadir}/droidmedia/

cp out/target/product/*/system/$DROIDLIB/libdroidmedia.so \
    $RPM_BUILD_ROOT/%{_libexecdir}/droid-hybris/system/$DROIDLIB/

cp out/target/product/*/system/$DROIDLIB/libminisf.so \
    $RPM_BUILD_ROOT/%{_libexecdir}/droid-hybris/system/$DROIDLIB/

cp out/target/product/*/system/bin/minimediaservice \
    $RPM_BUILD_ROOT/%{_libexecdir}/droid-hybris/system/bin/

cp out/target/product/*/system/bin/minisfservice \
    $RPM_BUILD_ROOT/%{_libexecdir}/droid-hybris/system/bin/

cp external/droidmedia/*.h $RPM_BUILD_ROOT/%{_includedir}/droidmedia/
cp external/droidmedia/hybris.c $RPM_BUILD_ROOT/%{_datadir}/droidmedia/

LIBDMSOLOC=$RPM_BUILD_ROOT/file.list
echo %{_libexecdir}/droid-hybris/system/$DROIDLIB/libdroidmedia.so >> %{LIBDMSOLOC}
echo %{_libexecdir}/droid-hybris/system/$DROIDLIB/libminisf.so >> %{LIBDMSOLOC}

%files -f %{LIBDMSOLOC}
%defattr(-,root,root,-)
%{_libexecdir}/droid-hybris/system/bin/minimediaservice
%{_libexecdir}/droid-hybris/system/bin/minisfservice

%files devel
%defattr(-,root,root,-)
%{_includedir}/droidmedia/*.h
%{_datadir}/droidmedia/hybris.c
