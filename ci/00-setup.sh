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
# 00-setup.sh
# CI first stage - SDK container setup
#
# Usage: ci/00-setup.sh git-SHA
#

set -e

GIT_SHA=$1

# Build SDK container
docker build .devcontainer -t amethyst-sdk:$GIT_SHA
