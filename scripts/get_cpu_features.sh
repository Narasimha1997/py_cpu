#!/bin/bash

function make_project () {

    PROJECT_ROOT=$1
    download=$2

    mkdir -p $PROJECT_ROOT/deps

    if [[ "$download" == "--download" ]]; then
        repo_url="https://github.com/google/cpu_features"
        git clone $repo_url
    fi

    if [[ ! -d "$PROJECT_ROOT/cpu_features" ]]; then
        echo "No such directory cpu_features in $PROJECT_ROOT, either download it manually or run the script with like"
        echo "script/get_cpu_info PROJECT_ROOT --download"
        exit
    fi

    pushd cpu_features
        mkdir build
        cd build && cmake .. && make
        mv libcpu_features.a $PROJECT_ROOT/deps/
        cd ..
        mv include/ $PROJECT_ROOT/deps/
    popd

    #remove the source repo
    rm -rf cpu_features

    echo "Built CPU features.."
}

make_project $1 $2