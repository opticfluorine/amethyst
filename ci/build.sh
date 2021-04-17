#!/bin/bash
#
# Amethyst MMORPG Engine
# Copyright (c) 2021 opticfluorine
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# build.sh
# Builds the Amethyst MMORPG engine.
#
# Usage: build.sh [-d|--debug] [-r|--repo DIR]
#

set -e

show_usage()
{
    echo "usage: build.sh [-d|--debug] [-r|--repo DIR]"
}

# Set default arguments.
BUILD_TYPE=Release
REPO=$PWD

# Parse arguments.
while [[ $# -gt 0 ]]
do
    key=$1
    case $key in
        -d|--debug)
            BUILD_TYPE=Debug
            shift
            ;;
        -r|--repo)
            REPO=$2
            shift
            shift
            ;;
        *)
            show_usage
            exit
            ;;
    esac
done

# Build.
mkdir -p $REPO/build/
cd $REPO/build/
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -GNinja ..
ninja
