#!/bin/sh
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
# 01-compile.sh
# CI second stage - compile Amethyst
#
# Usage: ci/01-compile.sh git-SHA workspace-dir
#

set -e

GIT_SHA=$1
WORKSPACE_DIR=$2

docker run \
    --rm \
    -v $WORKSPACE_DIR:/amethyst:rw \
    amethyst-sdk:$GIT_SHA  \
    /amethyst/ci/build.sh --repo $WORKSPACE_DIR
