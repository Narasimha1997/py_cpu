#!/bin/bash

function get_cpu_features () {

    repo_url="https://github.com/google/cpu_features"
    git clone $repo_url
    echo "Cloned cpu_features"
}

function get_pybind11 () {
    repo_url="https://github.com/pybind/pybind11"
    git clone https://github.com/pybind/pybind11
    pushd pybind11
    git checkout v2.6
    popd
}

get_cpu_features
get_pybind11