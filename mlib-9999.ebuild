# Copyright 2011 Gentoo Foundation

EAPI=3

inherit base cmake-utils git

CMAKE_MIN_VERSION="${CMAKE_MIN_VERSION:-2.8.6}"
CMAKE_BUILD_DIR="${WORKDIR}"
BUILD_DIR="${WORKDIR}"

DESCRIPTION="simple library on c++"
HOMEPAGE="https://github.com/AoD314/mlib"
#SRC_URI="mlib-0.1.0.zip"
SRC_URI=""
EGIT_REPO_URI="git://github.com/AoD314/mlib.git"

LICENSE="BSD"
SLOT="0"
KEYWORDS="amd64 ~x86"

#PROPERTIES="interactive"

IUSE="examples"
CMAKE_BUILD_TYPE="Release"

S="${WORKDIR}"

src_configure() {
	local mycmakeargs=( 
		$(cmake-utils_use_build examples)
	)
	cmake-utils_src_configure
}

src_install() {
	cmake-utils_src_install
}

src_compile() {
	cmake-utils_src_compile
}

