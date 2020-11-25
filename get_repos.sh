#!/bin/bash

function get_cpu_features () {

    repo_url="https://github.com/google/cpu_features"

    pushd src
    git clone $repo_url
    echo "Cloned cpu_features"
    popd
}

function get_pybind11 () {
    repo_url="https://github.com/pybind/pybind11"
    pushd src
    git clone $repo_url
    pushd pybind11
    git checkout stable
    popd
    popd
}

get_cpu_features
get_pybind11