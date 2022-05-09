#!/usr/bin/env bash

setup_linux() {
  # Because of how bare-bones our docker image is
  echo "::group::Install prerequisites"
  apt-get -yq install software-properties-common
  echo "::endgroup::"

  echo "::group::Add APT sources"
  for ppa in ppa:ubuntu-toolchain-r/test ppa:ubuntu-sdk-team/ppa \
             ppa:git-core/ppa ppa:beineri/opt-qt-5.15.2-xenial; do
    apt-add-repository -y "${ppa}"
  done
  echo "::endgroup::"

  echo "::group::Fetch APT updates"
  apt-get update -yq
  echo "::endgroup::"

  echo "::group::Install QT5"
  apt-get install -yq --no-install-suggests --no-install-recommends \
    build-essential qt5-default
    
  echo "::group::Install STK"
  apt-get install -yq --no-install-suggests --no-install-recommends \
    stk libstk-dev      
  echo "::endgroup::"
  
  echo "::group::Install cmake"
  apt-get install -yq cmake     
  echo "::endgroup::"

}

setup_macos() {
  echo "::group::Update Homebrew"
  brew update
  echo "::endgroup::"
  echo "::group::Install Homebrew packages"
  brew install libarchive qt@5
  brew link qt@5 --force
  brew install stk
  echo "/usr/local/opt/libarchive/bin" >> "${GITHUB_PATH}"
  echo "::endgroup::"

  #echo "::group::Install Python packages"
  #sudo pip3 install --upgrade oauth2client google-api-python-client
  #echo "::endgroup::"
}

setup_windows() {
  # Only 64 bit OpenSSL comes pre-installed
  if [ "${INPUT_ARCH%%_*}" = "win32" ]; then
    echo "::group::Install OpenSSL"
    choco install openssl.light --force --x86
    echo "::endgroup::"
  fi
  
  

  echo "::group::Install Python packages"
  pip install --upgrade oauth2client google-api-python-client
  echo "::endgroup::"
}

"setup_$(echo "${RUNNER_OS}" | tr '[A-Z]' '[a-z]')"
