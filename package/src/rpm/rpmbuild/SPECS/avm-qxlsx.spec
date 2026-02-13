Name:       avm-qxlsx
Version:    @PROJECT_VERSION_MAJOR@.@PROJECT_VERSION_MINOR@.@PROJECT_VERSION_PATCH@
Release:    1%{?dist}
Summary:    QXlsx for AVM-Energo projects

License:    GPLv3
URL:        https://git.avmenergo.ru/avm-energo/qxlsx.git
Source0:    https://git.avmenergo.ru/avm-energo/qxlsx.git

BuildArch:  ${arch}
BuildRequires:  cmake
Requires:
Provides:   avm-qxlsx

%description
LibZip library for AVM-Energo projects

%prep
%{__rm} -rf
%{__tar} -xzvf %{SOURCE0} -C rpmbuild/BUILD --strip-components 1

%build
cd rpmbuild/BUILD
%cmake -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_TOOLCHAIN_FILE=../../QXlsx/cmake/arch/${arch}.cmake -DCMAKE_INSTALL_PREFIX=rpmbuild/BUILDROOT
%cmake_build

%install
%cmake_install

%package devel

%description devel
LibZip library development files for AVM-Energo projects

%files
%license add-license-file-here
rpmbuild/BUILDROOT/avm-qxlsx.so*

%changelog
* Tue Dec 30 2025 anton <vao@asu-vei.ru>
- initial rpm build
